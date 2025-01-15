#include "chat_server.h"
#include "asio_context_pool.h"
#include "chat_session.h"

#include <fmt/printf.h>

ChatServer::ChatServer(net::io_context& ioc, std::uint16_t port)
  : m_ioc(ioc)
  , m_acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{
  fmt::println("[ChatServer] Listening on port {}", port);
  startAccept();
}

void
ChatServer::clearSession(std::string_view uuid)
{
  std::lock_guard<std::mutex> lock(m_mtx);
  m_sessions.erase(uuid.data());
}

void
ChatServer::handleAccept(ChatSessionPtr session,
                         const boost::system::error_code& error)
{
  if (!error) {
    session->start();
    std::lock_guard<std::mutex> lock(m_mtx);
    m_sessions.emplace(session->getUuid(), session);
  } else {
    fmt::println(
      "[ChatServer::handleAccept] Session accept failed, error is {}",
      error.what());
  }
  startAccept();
}

void
ChatServer::startAccept()
{
  auto& ioc = AsioContextPool::getInstance()->getIoContext();
  ChatSessionPtr session = std::make_shared<ChatSession>(ioc, this);
  m_acceptor.async_accept(
    session->getSocket(),
    std::bind(&ChatServer::handleAccept, this, session, std::placeholders::_1));
}
