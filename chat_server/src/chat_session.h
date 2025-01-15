#ifndef CHATSESSION_H
#define CHATSESSION_H

#include "global.h"
#include "message_node.h"

#include <boost/asio.hpp>

#include <memory>
#include <queue>

namespace net = boost::asio;
using net::ip::tcp;

class ChatServer;

class ChatSession : public std::enable_shared_from_this<ChatSession>
{
public:
  ChatSession(net::io_context& ioc, ChatServer* server);
  const std::string& getUuid() const;
  tcp::socket& getSocket();
  void start();
  void send(std::string_view message, MessageID id);
  void asyncReadBody(int length);
  void asyncReadHead(int totalLen);
  void close();

private:
  void asyncReadFull(int length,
                     const std::function<void(const boost::system::error_code&,
                                              std::size_t)>& handler);
  void asyncReadLen(int readLen,
                    int totalLen,
                    const std::function<void(const boost::system::error_code&,
                                             std::size_t)>& handler);
  void handlWrite(const boost::system::error_code& error,
                  std::shared_ptr<ChatSession> self);

private:
  tcp::socket m_socket;
  std::string m_uuid;
  ChatServer* m_server;
  std::mutex m_mtx;
  std::queue<SendNodePtr> m_sendQueue;
  char m_buffer[MAX_LENGTH];
  bool isHeadParse = false;
  MessageNodePtr m_recvHeadNode = nullptr;
  RecvNodePtr m_recvMessageNode = nullptr;
};
using ChatSessionPtr = std::shared_ptr<ChatSession>;

struct LogicNode
{
  LogicNode(const ChatSessionPtr& session, const RecvNodePtr& recvNode);
  ChatSessionPtr m_session;
  RecvNodePtr m_recvNode;
};
using LogicNodePtr = std::shared_ptr<LogicNode>;
#endif // CHATSESSION_H
