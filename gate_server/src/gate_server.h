#ifndef GATESERVER_H
#define GATESERVER_H

#include <memory>

#include <boost/asio.hpp>

namespace net = boost::asio;

class GateServer : public std::enable_shared_from_this<GateServer>
{
  using tcp = net::ip::tcp;

public:
  GateServer(net::io_context& ioc, unsigned short port);

  void start();

private:
  net::io_context& m_ioc;
  tcp::acceptor m_acceptor;
  tcp::socket m_socket;
};

#endif // GATESERVER_H
