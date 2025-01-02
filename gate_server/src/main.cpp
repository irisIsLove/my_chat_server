#include "gate_server.h"

#include <fmt/printf.h>

int
main()
{
  try {
    unsigned short port = 8080;
    net::io_context ioc{ 1 };
    net::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait(
      [&ioc](const boost::system::error_code& ec, int signalNumber) {
        if (ec) {
          return;
        }

        ioc.stop();
      });

    std::make_shared<GateServer>(ioc, port)->start();
    ioc.run();
  } catch (std::exception& e) {
    fmt::println(stderr, "Error: ", e.what());
  }
}