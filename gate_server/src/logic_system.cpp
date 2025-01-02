#include "logic_system.h"
#include "http_connection.h"

bool
LogicSystem::handleGet(const std::string& path,
                       const HttpConnectionPtr& connection)
{
  if (m_getHandlers.find(path) == m_getHandlers.end()) {
    return false;
  }

  m_getHandlers[path](connection);
  return true;
}

void
LogicSystem::registGet(std::string_view url, const HttpHandler& handler)
{
  m_getHandlers.emplace(url, handler);
}

LogicSystem::LogicSystem()
{
  registGet("/get_test", [](const std::shared_ptr<HttpConnection>& connection) {
    beast::ostream(connection->m_response.body()) << "receive get_test request";
  });
}
