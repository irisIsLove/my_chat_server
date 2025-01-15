#include "chat_session.h"
#include "chat_server.h"
#include "logic_system.h"

#include <boost/uuid.hpp>
#include <fmt/printf.h>

#include <functional>

ChatSession::ChatSession(net::io_context& ioc, ChatServer* server)
  : m_socket(ioc)
  , m_server(server)
{
  auto uuid = boost::uuids::random_generator()();
  m_uuid = boost::uuids::to_string(uuid);
  m_recvHeadNode = std::make_shared<MessageNode>(HEAD_TOTAL_LEN);
}

const std::string&
ChatSession::getUuid() const
{
  return m_uuid;
}

tcp::socket&
ChatSession::getSocket()
{
  return m_socket;
}

void
ChatSession::start()
{
  asyncReadHead(HEAD_TOTAL_LEN);
}

void
ChatSession::send(std::string_view message, MessageID id)
{
  std::lock_guard<std::mutex> lock(m_mtx);
  int queSize = m_sendQueue.size();
  if (queSize > MAX_SEND_QUEUE) {
    fmt::println("[ChatSession::send] Send queue is full, size is {}",
                 MAX_SEND_QUEUE);
    return;
  }

  m_sendQueue.emplace(
    std::make_shared<SendNode>(message.data(), message.size(), id));
  if (queSize > 0) {
    return;
  }

  auto& node = m_sendQueue.front();
  net::async_write(m_socket,
                   net::buffer(node->m_data, node->m_totalLen),
                   std::bind(&ChatSession::handlWrite,
                             this,
                             std::placeholders::_1,
                             shared_from_this()));
}

void
ChatSession::asyncReadBody(int totalLen)
{
  auto self = shared_from_this();
  asyncReadFull(
    totalLen,
    [self, this, totalLen](const boost::system::error_code& ec,
                           std::size_t bytes_transferred) {
      try {
        if (ec) {
          fmt::println(
            "[ChatSession::asyncReadBody] Handle read failed, error is {}",
            ec.what());
          close();
          m_server->clearSession(m_uuid);
          return;
        }

        if (bytes_transferred < totalLen) {
          fmt::println("[ChatSession::asyncReadBody] Read length not match, "
                       "read {}, total {}",
                       bytes_transferred,
                       totalLen);
          close();
          m_server->clearSession(m_uuid);
          return;
        }

        std::memcpy(m_recvMessageNode->m_data, m_buffer, bytes_transferred);
        m_recvMessageNode->m_curLen += bytes_transferred;
        m_recvMessageNode->m_data[m_recvMessageNode->m_totalLen] = '\0';
        fmt::println("[ChatSession::asyncReadBody] Receive message is {}",
                     m_recvMessageNode->m_data);

        LogicSystem::getInstance()->postMessageToQue(
          std::make_shared<LogicNode>(shared_from_this(), m_recvMessageNode));
        asyncReadHead(HEAD_TOTAL_LEN);
      } catch (std::exception& e) {
      }
    });
}

void
ChatSession::asyncReadHead(int length)
{
  auto self = shared_from_this();
  asyncReadFull(
    HEAD_TOTAL_LEN,
    [self, this](const boost::system::error_code& ec,
                 std::size_t bytes_transferred) {
      try {
        if (ec) {
          fmt::println("[ChatSession::asyncReadHead] Handle "
                       "read failed, error is {}",
                       ec.what());
          close();
          m_server->clearSession(m_uuid);
          return;
        }

        if (bytes_transferred < HEAD_TOTAL_LEN) {
          fmt::println("[ChatSession::asyncReadHead] Handle "
                       "read failed, bytes_transferred is {}",
                       bytes_transferred);
          close();
          m_server->clearSession(m_uuid);
          return;
        }

        m_recvHeadNode->clear();
        std::memcpy(m_recvHeadNode->m_data, m_buffer, bytes_transferred);

        std::uint16_t id = 0;
        std::memcpy(&id, m_recvHeadNode->m_data, HEAD_ID_LEN);
        id = net::detail::socket_ops::host_to_network_short(id);
        fmt::println("[ChatSession::asyncReadHead] Message Id is {}", id);
        if (id > MAX_LENGTH) {
          fmt::println("[ChatSession::asyncReadHead] Message "
                       "Id is invalid, clear session");
          m_server->clearSession(m_uuid);
          return;
        }

        std::uint16_t messageLen = 0;
        std::memcpy(
          &messageLen, m_recvHeadNode->m_data + HEAD_ID_LEN, HEAD_DATA_LEN);
        messageLen = net::detail::socket_ops::host_to_network_short(messageLen);
        fmt::println("[ChatSession::asyncReadHead] Message len is {}",
                     messageLen);
        if (messageLen > MAX_LENGTH) {
          fmt::println("[ChatSession::asyncReadHead] Message "
                       "len is invalid, clear session");
          m_server->clearSession(m_uuid);
          return;
        }

        m_recvMessageNode =
          std::make_shared<RecvNode>(messageLen, static_cast<MessageID>(id));
        asyncReadBody(messageLen);
      } catch (std::exception& e) {
        fmt::println("[ChatSession::asyncReadHead] Exception is", e.what());
      }
    });
}

void
ChatSession::close()
{
  m_socket.close();
}

void
ChatSession::asyncReadFull(
  int length,
  const std::function<void(const boost::system::error_code&, std::size_t)>&
    handler)
{
  std::memset(m_buffer, 0, length);
  asyncReadLen(0, length, handler);
}

void
ChatSession::asyncReadLen(
  int readLen,
  int totalLen,
  const std::function<void(const boost::system::error_code&, std::size_t)>&
    handler)
{
  auto self = shared_from_this();
  m_socket.async_read_some(
    net::buffer(m_buffer + readLen, totalLen - readLen),
    [this, self, readLen, totalLen, handler](
      const boost::system::error_code& ec, std::size_t bytes_transferred) {
      if (ec || readLen + bytes_transferred >= totalLen) {
        handler(ec, readLen + bytes_transferred);
        return;
      }
      asyncReadLen(readLen + bytes_transferred, totalLen, handler);
    });
}

void
ChatSession::handlWrite(const boost::system::error_code& error,
                        std::shared_ptr<ChatSession> self)
{
  try {
    if (!error) {
      std::lock_guard<std::mutex> lock(m_mtx);
      m_sendQueue.pop();
      if (!m_sendQueue.empty()) {
        auto& node = m_sendQueue.front();
        net::async_write(
          m_socket,
          net::buffer(node->m_data, node->m_totalLen),
          std::bind(
            &ChatSession::handlWrite, this, std::placeholders::_1, self));
      }
    } else {
      fmt::println("[ChatSession::handlWrite] Handle write failed, error is {}",
                   error.what());
      close();
      m_server->clearSession(m_uuid);
    }
  } catch (std::exception& e) {
    fmt::println("[ChatSession::handlWrite] Exception is", e.what());
  }
}

LogicNode::LogicNode(const ChatSessionPtr& session, const RecvNodePtr& recvNode)
  : m_session(session)
  , m_recvNode(recvNode)
{
}
