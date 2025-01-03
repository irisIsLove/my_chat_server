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
  for (auto& work : m_works) {
    work->get_io_context().stop();
    work.reset();
  }

  for (auto& thread : m_threads) {
    thread.join();
  }
}

AsioContextPool::AsioContextPool(std::size_t size)
  : m_ioContexts(size)
  , m_works(size)
{
  for (std::size_t i = 0; i < size; ++i) {
    m_works[i] = std::make_unique<Work>(m_ioContexts[i]);
  }

  for (std::size_t i = 0; i < size; ++i) {
    m_threads.emplace_back([this, i]() { m_ioContexts[i].run(); });
  }
}
