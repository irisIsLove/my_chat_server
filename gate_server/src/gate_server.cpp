#include "gate_server.h"
#include "asio_context_pool.h"
#include "http_connection.h"

GateServer::GateServer(net::io_context& ioc, unsigned short port)
  : m_ioc(ioc)
  , m_acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{
}

void
GateServer::start()
{
  auto self = shared_from_this();
  net::io_context& ioc = AsioContextPool::getInstance()->getIoContext();
  std::shared_ptr<HttpConnection> newCon =
    std::make_shared<HttpConnection>(ioc);
  m_acceptor.async_accept(newCon->getSocket(),
                          [self, newCon](const boost::system::error_code& ec) {
                            try {
                              if (ec) {
                                self->start();
                                return;
                              }
                              newCon->start();
                              self->start();
                            } catch (std::exception& e) {
                            }
                          });
}
