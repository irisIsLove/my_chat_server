#include "asio_context_pool.h"
#include "chat_server.h"
#include "config_manager.h"

#include <fmt/printf.h>

int
main()
{
  try {
    auto& config = ConfigManager::getInstance();
    auto ioPool = AsioContextPool::getInstance();
    net::io_context ioc;
    net::signal_set signals(ioc, SIGINT, SIGTERM);

    signals.async_wait(
      [&ioc, ioPool](boost::system::error_code /*ec*/, int /*signo*/) {
        ioc.stop();
        ioPool->stop();
      });

    auto strPort = config["SelfServer"]["port"];
    ChatServer server(ioc, std::stoi(strPort));

    ioc.run();
  } catch (std::exception& e) {
    fmt::println(stderr, "Excepttion: {}", e.what());
  }
}