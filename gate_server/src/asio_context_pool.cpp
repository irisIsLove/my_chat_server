#include "asio_context_pool.h"

AsioContextPool::~AsioContextPool()
{
  stop();
  fmt::println("AsioContextPool::~AsioContextPool()");
}

boost::asio::io_context&
AsioContextPool::getIoContext()
{
  auto& ioContext = m_ioContexts[m_nextIoContext++];
  if (m_nextIoContext == m_ioContexts.size()) {
    m_nextIoContext = 0;
  }
  return ioContext;
}

void
AsioContextPool::stop()
{
  for (auto& work : m_workGuards) {
    work.reset();
  }

  for (auto& thread : m_threads) {
    thread.join();
  }
}

AsioContextPool::AsioContextPool(std::size_t size)
  : m_ioContexts(size)
{
  for (std::size_t i = 0; i < size; ++i) {
    auto&& t = boost::asio::make_work_guard(m_ioContexts[i]);
    m_workGuards.emplace_back(boost::asio::make_work_guard(m_ioContexts[i]));
  }

  for (std::size_t i = 0; i < size; ++i) {
    m_threads.emplace_back([this, i]() { m_ioContexts[i].run(); });
  }
}
