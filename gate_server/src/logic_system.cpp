#include "logic_system.h"
#include "global.h"
#include "http_connection.h"
#include "mysql_manager.h"
#include "redis_manager.h"
#include "status_grpc_client.h"
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
      fmt::println("[get_varify_code]: receive body is {}", strBody);
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

  registPost(
    "/user_register", [](const std::shared_ptr<HttpConnection>& connection) {
      auto strBody =
        beast::buffers_to_string(connection->m_request.body().data());
      fmt::println("[user_register]: receive body is {}", strBody);
      connection->m_response.set(http::field::content_type, "text/json");

      Json::Value root, srcRoot;
      Json::Reader reader;
      bool isParse = reader.parse(strBody, srcRoot);
      if (!isParse) {
        fmt::println("Failed to parse JSON data!");
        root["error"] = static_cast<int>(ErrorCode::ERR_JSON);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      std::string strCode;
      bool isGetVarify = RedisManager::getInstance()->get(
        CODE_PRIFIX + srcRoot["email"].asString(), strCode);
      if (!isGetVarify) {
        fmt::println("Get varify code exprired!");
        root["error"] = static_cast<int>(ErrorCode::ERR_VARIFY_EXPIRED);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      if (srcRoot["code"].asString() != strCode) {
        fmt::println("Varify code is not match!");
        root["error"] = static_cast<int>(ErrorCode::ERR_VARIFY_CODE);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      int uid =
        MysqlManager::getInstance()->registerUser(srcRoot["user"].asString(),
                                                  srcRoot["email"].asString(),
                                                  srcRoot["pass"].asString());
      if (uid == 0 || uid == -1) {
        fmt::println("User or email has been registered!");
        root["error"] = static_cast<int>(ErrorCode::ERR_USER_EXIST);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      root["error"] = static_cast<int>(ErrorCode::SUCCESS);
      root["user"] = srcRoot["user"].asString();
      root["pass"] = srcRoot["pass"].asString();
      root["email"] = srcRoot["email"].asString();
      root["uid"] = uid;
      beast::ostream(connection->m_response.body()) << root.toStyledString();
    });

  registPost(
    "/reset_pass", [](const std::shared_ptr<HttpConnection>& connection) {
      auto strBody =
        beast::buffers_to_string(connection->m_request.body().data());
      fmt::println("[reset_pass]: receive body is {}", strBody);
      connection->m_response.set(http::field::content_type, "text/json");

      Json::Value root, srcRoot;
      Json::Reader reader;
      bool isParse = reader.parse(strBody, srcRoot);
      if (!isParse) {
        fmt::println("Failed to parse JSON data!");
        root["error"] = static_cast<int>(ErrorCode::ERR_JSON);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      std::string strCode;
      bool isGetVarify = RedisManager::getInstance()->get(
        CODE_PRIFIX + srcRoot["email"].asString(), strCode);
      if (!isGetVarify) {
        fmt::println("Get varify code exprired!");
        root["error"] = static_cast<int>(ErrorCode::ERR_VARIFY_EXPIRED);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      if (srcRoot["code"].asString() != strCode) {
        fmt::println("Varify code is not match!");
        root["error"] = static_cast<int>(ErrorCode::ERR_VARIFY_CODE);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      std::string name = srcRoot["user"].asString();
      std::string email = srcRoot["email"].asString();
      std::string pass = srcRoot["pass"].asString();
      bool isEmailValid = MysqlManager::getInstance()->checkEmail(name, email);
      if (!isEmailValid) {
        fmt::println("User email not match!");
        root["error"] = static_cast<int>(ErrorCode::ERR_EMAIL_NOT_MATCH);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      bool isReset = MysqlManager::getInstance()->updatePass(name, pass);
      if (!isReset) {
        fmt::println("Reset password failed!");
        root["error"] = static_cast<int>(ErrorCode::ERR_PASS_UP_FAIL);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      fmt::println("Reset password success!");
      root["error"] = static_cast<int>(ErrorCode::SUCCESS);
      root["email"] = email;
      beast::ostream(connection->m_response.body()) << root.toStyledString();
    });

  registPost(
    "/user_login", [](const std::shared_ptr<HttpConnection>& connection) {
      auto strBody =
        beast::buffers_to_string(connection->m_request.body().data());
      fmt::println("[user_login]: receive body is {}", strBody);
      connection->m_response.set(http::field::content_type, "text/json");

      Json::Value root, srcRoot;
      Json::Reader reader;
      bool isParse = reader.parse(strBody, srcRoot);
      if (!isParse) {
        fmt::println("Failed to parse JSON data!");
        root["error"] = static_cast<int>(ErrorCode::ERR_JSON);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      auto email = srcRoot["email"].asString();
      auto pass = srcRoot["pass"].asString();
      UserInfo user;

      // TODO: check email and pass
      bool isPassValid =
        MysqlManager::getInstance()->checkPass(email, pass, user);
      if (!isPassValid) {
        fmt::println("User password not match!");
        root["error"] = static_cast<int>(ErrorCode::ERR_PASS_INVALID);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      // StatusServer verify
      auto reply = StatusGrpcClient::getInstance()->getChatServer(user.uid);
      if (reply.error()) {
        fmt::println("Grpc get chat server failed, error is {}", reply.error());
        root["error"] = static_cast<int>(ErrorCode::ERR_RPC);
        beast::ostream(connection->m_response.body()) << root.toStyledString();
        return;
      }

      fmt::println("Success to load userinfo uid is {}", user.uid);
      root["error"] = static_cast<int>(ErrorCode::SUCCESS);
      root["uid"] = user.uid;
      root["token"] = reply.token();
      root["host"] = reply.host();
      root["port"] = reply.port();
      root["email"] = email;
      beast::ostream(connection->m_response.body()) << root.toStyledString();
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
