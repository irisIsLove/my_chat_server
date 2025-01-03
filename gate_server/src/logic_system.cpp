#include "logic_system.h"
#include "global.h"
#include "http_connection.h"
#include "varify_grpc_client.h"

#include <json/json.h>

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
    beast::ostream(connection->m_response.body())
      << "receive get_test request\n";
    int i = 0;
    for (const auto& elem : connection->m_getParams) {
      beast::ostream(connection->m_response.body())
        << "parm: " << i++ << ": " << elem.first << " = " << elem.second
        << "\n";
    }
  });

  registPost(
    "/get_varify_code", [](const std::shared_ptr<HttpConnection>& connection) {
      auto strBody =
        beast::buffers_to_string(connection->m_request.body().data());
      fmt::println("receive body is {}", strBody);
      connection->m_response.set(http::field::content_type, "text/json");
      Json::Value root;
      Json::Reader reader;
      Json::Value srcRoot;

      bool isParse = reader.parse(strBody, srcRoot);
      if (!isParse || !srcRoot.isMember("email")) {
        fmt::println("Failed to parse JSON data!");
        root["error"] = static_cast<int>(ErrorCode::ERR_JSON);
        auto strJson = root.toStyledString();
        beast::ostream(connection->m_response.body()) << strJson;
        return;
      }

      auto email = srcRoot["email"].asString();
      auto reply = VarifyGrpcClient::getInstance()->getVarifyCode(email);
      root["error"] = static_cast<int>(ErrorCode::SUCCESS);
      root["email"] = email;
      auto strJson = root.toStyledString();
      beast::ostream(connection->m_response.body()) << strJson;
    });
}

void
LogicSystem::registPost(std::string_view url, const HttpHandler& handler)
{
  m_postHandlers.emplace(url, handler);
}

bool
LogicSystem::handlePost(const std::string& path,
                        const HttpConnectionPtr& connection)
{
  if (m_postHandlers.find(path) == m_postHandlers.end()) {
    return false;
  }

  m_postHandlers[path](connection);
  return true;
}
