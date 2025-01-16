#include "status_server_impl.h"
#include "config_manager.h"
#include "global.h"

#include <boost/uuid.hpp>
#include <fmt/printf.h>

StatusServerImpl::StatusServerImpl()
{
  auto& config = ConfigManager::getInstance();

  ChatServer server1{ config["ChatServer1"]["host"],
                      config["ChatServer1"]["port"],
                      config["ChatServer1"]["name"],
                      0 };
  m_servers.emplace(server1.name, server1);

  ChatServer server2{ config["ChatServer2"]["host"],
                      config["ChatServer2"]["port"],
                      config["ChatServer2"]["name"],
                      0 };
  m_servers.emplace(server2.name, server2);
}

Status
StatusServerImpl::GetChatServer(ServerContext* context,
                                const GetChatServerRequest* request,
                                GetChatServerResponse* response)
{
  fmt::println("[StatusServerImpl::GetChatServer]: data has received");
  const auto& server = getChatServer();
  response->set_host(server.host);
  response->set_port(server.port);
  response->set_error(static_cast<int>(ErrorCode::SUCCESS));
  response->set_token(generatorUuid());
  insertToken(request->uid(), response->token());
  return Status::OK;
}

Status
StatusServerImpl::Login(ServerContext* context,
                        const LoginRequest* request,
                        LoginResponse* response)
{
  std::lock_guard<std::mutex> lock(m_mtxToken);

  auto uid = request->uid();
  auto token = request->token();
  auto iter = m_tokens.find(uid);
  if (iter == m_tokens.end()) {
    response->set_error(static_cast<int>(ErrorCode::ERR_UID_INVALID));
    return Status::OK;
  }
  if (iter->second != token) {
    response->set_error(static_cast<int>(ErrorCode::ERR_TOKEN_INVALID));
    return Status::OK;
  }

  response->set_error(static_cast<int>(ErrorCode::SUCCESS));
  response->set_uid(uid);
  response->set_token(token);
  return Status::OK;
}

void
StatusServerImpl::insertToken(int uid, std::string_view token)
{
  std::lock_guard<std::mutex> lock(m_mtxToken);
  m_tokens[uid] = token;
}

ChatServer
StatusServerImpl::getChatServer()
{
  std::lock_guard<std::mutex> lock(m_mtxServer);
  auto minServer = m_servers.begin()->second;
  for (auto& server : m_servers) {
    if (server.second.connectCount <= minServer.connectCount &&
        !server.second.host.empty()) {
      minServer = server.second;
    }
  }
  return minServer;
}

std::string
StatusServerImpl::generatorUuid()
{
  boost::uuids::uuid uuid = boost::uuids::random_generator()();
  return boost::uuids::to_string(uuid);
}
