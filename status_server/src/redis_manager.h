#ifndef REDISMANAGER_H
#define REDISMANAGER_H

#include "singleton.h"

#include <hiredis/hiredis.h>

#include <atomic>
#include <condition_variable>
#include <queue>

using RedisContextPtr = std::unique_ptr<redisContext, decltype(&redisFree)>;
using RedisReplyPtr = std::unique_ptr<redisReply, decltype(&freeReplyObject)>;

class RedisConnectionPool
{
public:
  RedisConnectionPool(std::size_t poolSize,
                      std::string_view host,
                      int port,
                      std::string_view password);
  ~RedisConnectionPool();

  RedisContextPtr getContext();
  void returnContext(RedisContextPtr context);
  void close();

private:
  std::atomic<bool> m_isStop = false;
  std::mutex m_mtx;
  std::condition_variable m_cond;
  std::queue<RedisContextPtr> m_contexts;
};

class RedisManager : public Singleton<RedisManager>
{
  friend class Singleton<RedisManager>;

public:
  ~RedisManager();

  bool get(std::string_view key, std::string& value);
  bool set(std::string_view key, std::string_view value);
  bool lPush(std::string_view key, std::string_view value);
  bool lPop(std::string_view key, std::string& value);
  bool rPush(std::string_view key, std::string_view value);
  bool rPop(std::string_view key, std::string& value);
  bool hSet(std::string_view key,
            std::string_view field,
            std::string_view value);
  std::string hGet(std::string_view key, std::string_view field);
  bool del(std::string_view key);
  bool existsKey(std::string_view key);
  void close();

private:
  RedisManager();

private:
  std::unique_ptr<RedisConnectionPool> m_pool;
};

#endif // REDISMANAGER_H
