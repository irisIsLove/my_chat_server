#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <boost/asio.hpp>

#include <mutex>
#include <unordered_map>

namespace net = boost::asio;
using net::ip::tcp;
class ChatSession;
using ChatSessionPtr = std::shared_ptr<ChatSession>;

class ChatServer
{
public:
  ChatServer(net::io_context& ioc, std::uint16_t port);
  void clearSession(std::string_view uuid);

private:
  void handleAccept(ChatSessionPtr session,
                    const boost::system::error_code& error);
  void startAccept();

private:
  net::io_context& m_ioc;
  tcp::acceptor m_acceptor;
  std::mutex m_mtx;
  std::unordered_map<std::string, ChatSessionPtr> m_sessions;
};

#endif // CHATSERVER_H
