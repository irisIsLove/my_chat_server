#include "config_manager.h"
#include "gate_server.h"
#include "redis_manager.h"

#include <fmt/printf.h>
#include <hiredis/hiredis.h>

void
testRedis()
{
  std::unique_ptr<redisContext, decltype(&redisFree)> c(
    redisConnect("127.0.0.1", 6379), redisFree);
  if (c->err) {
    fmt::println("Connected to redis error: {}", c->errstr);
    return;
  }
  fmt::println("Connected to redis successfully");

  std::string_view pass = "157158";
  using ReplyPtr = std::unique_ptr<redisReply, decltype(&freeReplyObject)>;
  ReplyPtr reply(
    static_cast<redisReply*>(redisCommand(c.get(), "AUTH %s", pass.data())),
    freeReplyObject);
  if (reply->type == REDIS_REPLY_ERROR) {
    fmt::println("AUTH failed!");
  } else {
    fmt::println("AUTH success!");
  }

  std::string_view command1 = "set stest1 value1";
  reply.reset(static_cast<redisReply*>(redisCommand(c.get(), command1.data())));
  if (reply == nullptr) {
    fmt::println("Excute command1 failed!");
  }

  if (!(reply->type == REDIS_REPLY_STATUS &&
          (std::strcmp(reply->str, "OK") == 0) ||
        std::strcmp(reply->str, "ok") == 0)) {
    fmt::println("Excute command[{}] failed!", command1);
    return;
  }
  fmt::println("Successful to excute command[{}]!", command1);

  std::string_view command2 = "strlen stest1";
  reply.reset(static_cast<redisReply*>(redisCommand(c.get(), command2.data())));
  if (reply->type != REDIS_REPLY_INTEGER) {
    fmt::println("Excute command[{}] failed!", command2);
    return;
  }

  fmt::println(
    "Successful to excute command[{}]!\n result: The length of 'stest1' is {}",
    command2,
    reply->integer);

  std::string_view command3 = "get stest1";
  reply.reset(static_cast<redisReply*>(redisCommand(c.get(), command3.data())));
  if (reply->type != REDIS_REPLY_STRING) {
    fmt::println("Excute command[{}] failed!", command3);
    return;
  }
  fmt::println(
    "Successful to excute command[{}]!\n result: The value of 'stest1' is {}",
    command3,
    reply->str);

  std::string_view command4 = "get stest2";
  reply.reset(static_cast<redisReply*>(redisCommand(c.get(), command4.data())));
  if (reply->type != REDIS_REPLY_NIL) {
    fmt::println("Excute command[{}] failed!", command4);
    return;
  }
  fmt::println("Successful to excute command[{}]!", command4);
}

void
testRedisManager()
{
  auto redis = RedisManager::getInstance();
  assert(redis->set("blogwebsite", "llfc.club"));
  std::string value{};
  assert(redis->get("blogwebsite", value));
  assert(redis->get("nonekey", value) == false);
  assert(redis->hSet("bloginfo", "blogwebsite", "llfc.club"));
  assert(redis->hGet("bloginfo", "blogwebsite") != "");
  assert(redis->existsKey("bloginfo"));
  assert(redis->del("bloginfo"));
  assert(redis->del("bloginfo"));
  assert(redis->existsKey("bloginfo") == false);
  assert(redis->lPush("lpushkey1", "lpushvalue1"));
  assert(redis->lPush("lpushkey1", "lpushvalue2"));
  assert(redis->lPush("lpushkey1", "lpushvalue3"));
  assert(redis->rPop("lpushkey1", value));
  assert(redis->rPop("lpushkey1", value));
  assert(redis->lPop("lpushkey1", value));
  assert(redis->lPop("lpushkey2", value) == false);
}

int
main()
{
  auto& ConfigManager = ConfigManager::getInstance();
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