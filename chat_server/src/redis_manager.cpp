#include "redis_manager.h"
#include "config_manager.h"
#include "global.h"

#include <fmt/format.h>

RedisConnectionPool::RedisConnectionPool(std::size_t poolSize,
                                         std::string_view host,
                                         int port,
                                         std::string_view password)
{
  for (std::size_t i = 0; i < poolSize; ++i) {
    RedisContextPtr context(redisConnect(host.data(), port), redisFree);
    if (context == nullptr || context->err != 0)
      continue;

    RedisReplyPtr reply(static_cast<redisReply*>(redisCommand(
                          context.get(), "AUTH %s", password.data())),
                        freeReplyObject);
    if (reply->type == REDIS_REPLY_ERROR) {
      fmt::println("Auth failed!");
      continue;
    }

    fmt::println("Auth succeed!");
    m_contexts.emplace(std::move(context));
  }
}

RedisConnectionPool::~RedisConnectionPool()
{
  std::lock_guard<std::mutex> lock(m_mtx);
  while (!m_contexts.empty()) {
    m_contexts.pop();
  }
}

RedisContextPtr
RedisConnectionPool::getContext()
{
  std::unique_lock<std::mutex> lock(m_mtx);
  m_cond.wait(lock, [this]() {
    if (m_isStop)
      return true;
    return !m_contexts.empty();
  });

  if (m_isStop)
    return RedisContextPtr(nullptr, nullptr);

  auto context = std::move(m_contexts.front());
  m_contexts.pop();
  return context;
}

void
RedisConnectionPool::returnContext(RedisContextPtr context)
{
  std::lock_guard<std::mutex> lock(m_mtx);
  if (m_isStop)
    return;
  m_contexts.push(std::move(context));
  m_cond.notify_one();
}

void
RedisConnectionPool::close()
{
  m_isStop = true;
  m_cond.notify_all();
}

RedisManager::~RedisManager()
{
  close();
}

bool
RedisManager::get(std::string_view key, std::string& value)
{
  auto context = m_pool->getContext();
  if (context == nullptr)
    return false;

  RedisReplyPtr reply(
    static_cast<redisReply*>(redisCommand(context.get(), "GET %s", key.data())),
    freeReplyObject);
  if (reply == nullptr || reply->type != REDIS_REPLY_STRING) {
    fmt::println("[ GET {} ] failed", key);
    m_pool->returnContext(std::move(context));
    return false;
  }

  value = reply->str;
  fmt::println("Succeed to execute command [ GET {} ]", key);
  m_pool->returnContext(std::move(context));
  return true;
}

bool
RedisManager::set(std::string_view key, std::string_view value)
{
  auto context = m_pool->getContext();
  if (context == nullptr)
    return false;

  RedisReplyPtr reply(static_cast<redisReply*>(redisCommand(
                        context.get(), "SET %s %s", key.data(), value.data())),
                      freeReplyObject);
  if (reply == nullptr || (reply->type == REDIS_REPLY_STATUS &&
                           std::strcmp(reply->str, "OK") != 0 &&
                           std::strcmp(reply->str, "ok") != 0)) {
    m_pool->returnContext(std::move(context));
    fmt::println("Execute command [ SET {} {} ] failed", key, value);
    return false;
  }

  m_pool->returnContext(std::move(context));
  fmt::println("Succeed to execute command [ SET {} {} ]", key, value);
  return true;
}

bool
RedisManager::lPush(std::string_view key, std::string_view value)
{
  auto context = m_pool->getContext();
  if (context == nullptr)
    return false;

  RedisReplyPtr reply(
    static_cast<redisReply*>(
      redisCommand(context.get(), "LPUSH %s %s", key.data(), value.data())),
    freeReplyObject);
  if (reply == nullptr ||
      (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0)) {
    m_pool->returnContext(std::move(context));
    fmt::println("Execute command [ LPUSH {} {} ] failed", key, value);
    return false;
  }

  m_pool->returnContext(std::move(context));
  fmt::println("Succeed to execute command [ LPUSH {} {} ]", key, value);
  return true;
}

bool
RedisManager::lPop(std::string_view key, std::string& value)
{
  auto context = m_pool->getContext();
  if (context == nullptr)
    return false;

  RedisReplyPtr reply(static_cast<redisReply*>(
                        redisCommand(context.get(), "LPOP %s", key.data())),
                      freeReplyObject);
  if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
    m_pool->returnContext(std::move(context));
    fmt::println("Execute command [ LPOP {} ] failed", key);
    return false;
  }

  value = reply->str;
  m_pool->returnContext(std::move(context));
  fmt::println("Succeed to execute command [ LPOP {} ]", key);
  return true;
}

bool
RedisManager::rPush(std::string_view key, std::string_view value)
{
  auto context = m_pool->getContext();
  if (context == nullptr)
    return false;

  RedisReplyPtr reply(
    static_cast<redisReply*>(
      redisCommand(context.get(), "RPUSH %s %s", key.data(), value.data())),
    freeReplyObject);
  if (reply == nullptr ||
      (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0)) {
    m_pool->returnContext(std::move(context));
    fmt::println("Execute command [ RPUSH {} {} ] failed", key, value);
    return false;
  }

  m_pool->returnContext(std::move(context));
  fmt::println("Succeed to execute command [ RPUSH {} {} ]", key, value);
  return true;
}

bool
RedisManager::rPop(std::string_view key, std::string& value)
{
  auto context = m_pool->getContext();
  if (context == nullptr)
    return false;

  RedisReplyPtr reply(static_cast<redisReply*>(
                        redisCommand(context.get(), "RPOP %s", key.data())),
                      freeReplyObject);
  if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
    m_pool->returnContext(std::move(context));
    fmt::println("Execute command [ RPOP {} ] failed", key);
    return false;
  }

  value = reply->str;
  m_pool->returnContext(std::move(context));
  fmt::println("Succeed to execute command [ RPOP {} ]", key);
  return true;
}

bool
RedisManager::hSet(std::string_view key,
                   std::string_view field,
                   std::string_view value)
{
  auto context = m_pool->getContext();
  if (context == nullptr)
    return false;

  RedisReplyPtr reply(
    static_cast<redisReply*>(redisCommand(
      context.get(), "HSET %s %s %s", key.data(), field.data(), value.data())),
    freeReplyObject);
  if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
    m_pool->returnContext(std::move(context));
    fmt::println("Execute command [ HSET {} {} {} ] failed", key, field, value);
    return false;
  }

  m_pool->returnContext(std::move(context));
  fmt::println(
    "Succeed to execute command [ HSET {} {} {} ]", key, field, value);
  return true;
}

std::string
RedisManager::hGet(std::string_view key, std::string_view field)
{
  auto context = m_pool->getContext();
  if (context == nullptr)
    return "";

  RedisReplyPtr reply(static_cast<redisReply*>(redisCommand(
                        context.get(), "HGET %s %s", key.data(), field.data())),
                      freeReplyObject);
  if (reply == nullptr || reply->type == REDIS_REPLY_NIL) {
    m_pool->returnContext(std::move(context));
    fmt::println("Execute command [ HGET {} {} ] failed", key, field);
    return {};
  }

  m_pool->returnContext(std::move(context));
  fmt::println("Succeed to execute command [ HGET {} {} ]", key, field);
  return reply->str;
}

bool
RedisManager::del(std::string_view key)
{
  auto context = m_pool->getContext();
  if (context == nullptr)
    return false;

  RedisReplyPtr reply(
    static_cast<redisReply*>(redisCommand(context.get(), "DEL %s", key.data())),
    freeReplyObject);
  if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER) {
    m_pool->returnContext(std::move(context));
    fmt::println("[ DEL {} ] failed", key);
    return false;
  }

  m_pool->returnContext(std::move(context));
  fmt::println("Succeed to execute command [ DEL {} ]", key);
  return true;
}

bool
RedisManager::existsKey(std::string_view key)
{
  auto context = m_pool->getContext();
  if (context == nullptr)
    return false;

  RedisReplyPtr reply(static_cast<redisReply*>(
                        redisCommand(context.get(), "EXISTS %s", key.data())),
                      freeReplyObject);
  if (reply == nullptr || reply->type != REDIS_REPLY_INTEGER ||
      reply->integer <= 0) {
    m_pool->returnContext(std::move(context));
    fmt::println("[ EXISTS {} ] failed", key);
    return false;
  }

  m_pool->returnContext(std::move(context));
  fmt::println("Succeed to execute command [ EXISTS {} ]", key);
  return true;
}

void
RedisManager::close()
{
  m_pool->close();
}

RedisManager::RedisManager()
{
  auto& config = ConfigManager::getInstance();
  auto host = config["Redis"]["host"];
  auto port = config["Redis"]["port"];
  auto pass = config["Redis"]["pass"];
  m_pool = std::make_unique<RedisConnectionPool>(
    MAX_POOL_SIZE, host, std::atoi(port.data()), pass);
};