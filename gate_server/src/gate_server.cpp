#include "gate_server.h"
#include "http_connection.h"

GateServer::GateServer(net::io_context& ioc, unsigned short port)
  : m_ioc(ioc)
  , m_acceptor(ioc, tcp::endpoint(tcp::v4(), port))
  , m_socket(ioc)
{
}

void
GateServer::start()
{
  auto self = shared_from_this();
  m_acceptor.async_accept(m_socket, [self](boost::system::error_code ec) {
    try {
      if (ec) {
        self->start();
        return;
      }
      std::make_shared<HttpConnection>(std::move(self->m_socket))->start();
      self->start();
    } catch (std::exception& e) {
    }
  });
}
