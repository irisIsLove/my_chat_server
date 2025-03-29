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
  using WokrGuards = std::vector<
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type>>;

public:
  ~AsioContextPool();

  boost::asio::io_context& getIoContext();
  void stop();

private:
  AsioContextPool(std::size_t size = std::thread::hardware_concurrency());

private:
  std::vector<IoContext> m_ioContexts;
  std::vector<std::thread> m_threads;
  WokrGuards m_workGuards;
  std::size_t m_nextIoContext = 0;
};

#endif // ASIOCONTEXTPOOL_H
