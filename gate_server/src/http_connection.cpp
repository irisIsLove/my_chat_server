#include "http_connection.h"
#include "logic_system.h"
#include "utils.h"

#include <fmt/format.h>

HttpConnection::HttpConnection(net::io_context& ioc)
  : m_socket(ioc)
{
}

void
HttpConnection::start()
{
  auto self = shared_from_this();
  http::async_read(
    m_socket,
    m_buffer,
    m_request,
    [self](const beast::error_code& ec, std::size_t bytes_transferred) {
      try {
        if (ec) {
          fmt::println("http read err is {}", ec.what());
          return;
        }

        boost::ignore_unused(bytes_transferred);
        self->handleRequest();
        self->checkDeadline();
      } catch (std::exception& e) {
        fmt::println("exception is {}", e.what());
      }
    });
}

net::ip::tcp::socket&
HttpConnection::getSocket()
{
  return m_socket;
}

void
HttpConnection::checkDeadline()
{
  auto self = shared_from_this();
  m_deadline.async_wait([self](const beast::error_code& ec) {
    if (!ec) {
      self->m_socket.close();
    }
  });
}

void
HttpConnection::writeResponse()
{
  auto self = shared_from_this();
  m_response.content_length(m_response.body().size());
  http::async_write(
    m_socket,
    m_response,
    [self](const beast::error_code& ec, std::size_t bytes_transferred) {
      self->m_socket.shutdown(tcp::socket::shutdown_send);
      self->m_deadline.cancel();
    });
}

void
HttpConnection::handleRequest()
{
  m_response.version(m_request.version());
  m_response.keep_alive();

  if (m_request.method() == http::verb::get) {
    preParseGetRequest();
    bool sucess =
      LogicSystem::getInstance()->handleGet(m_strGetUrl, shared_from_this());
    if (!sucess) {
      m_response.result(http::status::not_found);
      m_response.set(http::field::content_type, "text/plain");
      beast::ostream(m_response.body()) << "url not found\r\n";
      writeResponse();
      return;
    }

    m_response.result(http::status::ok);
    m_response.set(http::field::server, "GateServer");
    writeResponse();
    return;
  }

  if (m_request.method() == http::verb::post) {
    bool sucess = LogicSystem::getInstance()->handlePost(m_request.target(),
                                                         shared_from_this());
    if (!sucess) {
      m_response.result(http::status::not_found);
      m_response.set(http::field::content_type, "text/plain");
      beast::ostream(m_response.body()) << "url not found\r\n";
      writeResponse();
      return;
    }

    m_response.result(http::status::ok);
    m_response.set(http::field::server, "GateServer");
    writeResponse();
    return;
  }
}

void
HttpConnection::preParseGetRequest()
{
  auto url = m_request.target();
  auto queryPos = url.find('?');
  if (queryPos == std::string::npos) {
    m_strGetUrl = url;
    return;
  }

  m_strGetUrl = url.substr(0, queryPos);
  std::string strQuery = url.substr(queryPos + 1);
  std::size_t pos = 0;
  while ((pos = strQuery.find('&')) != std::string::npos) {
    auto pair = strQuery.substr(0, pos);
    std::size_t equalPos = pair.find('=');
    if (equalPos != std::string::npos) {
      std::string key = urlDecode(pair.substr(0, equalPos));
      std::string value = urlDecode(pair.substr(equalPos + 1));
      m_getParams.emplace(key, value);
    }
    strQuery.erase(0, pos + 1);
  }

  if (!strQuery.empty()) {
    std::size_t equalPos = strQuery.find('=');
    if (equalPos != std::string::npos) {
      std::string key = urlDecode(strQuery.substr(0, equalPos));
      std::string value = urlDecode(strQuery.substr(equalPos + 1));
      m_getParams.emplace(key, value);
    }
  }
}
