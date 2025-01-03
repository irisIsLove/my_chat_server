#include "config_manager.h"
#include "gate_server.h"

#include <fmt/printf.h>

int
main()
{
  ConfigManager ConfigManager;
  unsigned short port = std::atoi(ConfigManager["GateServer"]["port"].c_str());
  try {
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
    fmt::println("Gate Server listen on port: {}", port);
    ioc.run();
  } catch (std::exception& e) {
    fmt::println(stderr, "Error: ", e.what());
  }
}