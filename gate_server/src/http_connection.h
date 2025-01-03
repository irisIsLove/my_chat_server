#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <memory>
#include <unordered_map>

namespace net = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
  using tcp = net::ip::tcp;
  friend class LogicSystem;

public:
  HttpConnection(tcp::socket&& socket);

  void start();

private:
  void checkDeadline();
  void writeResponse();
  void handleRequest();
  void preParseGetRequest();

private:
  tcp::socket m_socket;
  beast::flat_buffer m_buffer{ 8196 };
  http::request<http::dynamic_body> m_request;
  http::response<http::dynamic_body> m_response;
  net::steady_timer m_deadline{ m_socket.get_executor(),
                                std::chrono::seconds(60) };
  std::unordered_map<std::string, std::string> m_getParams;
  std::string m_strGetUrl;
};

#endif // HTTPCONNECTION_H
