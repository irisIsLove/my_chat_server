#ifndef ASIOCONTEXTPOOL_H
#define ASIOCONTEXTPOOL_H

#include "singleton.h"

#include <boost/asio.hpp>

#include <thread>

class AsioContextPool : public Singleton<AsioContextPool>
{
  friend class Singleton<AsioContextPool>;

public:
  using IoContext = boost::asio::io_context;
  using Work = boost::asio::io_context::work;
  using WorkPtr = std::unique_ptr<Work>;

public:
  ~AsioContextPool();

  boost::asio::io_context& getIoContext();
  void stop();

private:
  AsioContextPool(std::size_t size = std::thread::hardware_concurrency());

private:
  std::vector<IoContext> m_ioContexts;
  std::vector<WorkPtr> m_works;
  std::vector<std::thread> m_threads;
  std::size_t m_nextIoContext = 0;
};

#endif // ASIOCONTEXTPOOL_H
