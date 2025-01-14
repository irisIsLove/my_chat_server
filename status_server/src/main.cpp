#include "config_manager.h"
#include "redis_manager.h"
#include "status_server_impl.h"

#include <boost/asio.hpp>
#include <fmt/printf.h>
#include <grpcpp/grpcpp.h>

int
main()
{
  try {
    auto& config = ConfigManager::getInstance();

    std::string address(config["StatusServer"]["host"] + ":" +
                        config["StatusServer"]["port"]);
    StatusServerImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    fmt::println("Server listening on {}", address);

    boost::asio::io_context ioc;
    boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
    signals.async_wait([&ioc](const boost::system::error_code& error, int) {
      if (!error) {
        fmt::println("Shutting down server...");
        ioc.stop();
      }
    });

    std::thread([&ioc]() { ioc.run(); }).detach();
    server->Wait();
  } catch (std::exception& e) {
    fmt::println(stderr, "Error: {}", e.what());
    RedisManager::getInstance()->close();
    return EXIT_FAILURE;
  }
}