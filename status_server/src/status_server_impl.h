#ifndef STATUSSERVERIMPL_H
#define STATUSSERVERIMPL_H

#include "messages/message.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using message::GetChatServerRequest;
using message::GetChatServerResponse;
using message::LoginRequest;
using message::LoginResponse;
using message::StatusService;

struct ChatServer
{
  std::string host;
  std::string port;
  std::string name;
  int connectCount;
};

class StatusServerImpl final : public StatusService::Service
{
public:
  StatusServerImpl();

  Status GetChatServer(ServerContext* context,
                       const GetChatServerRequest* request,
                       GetChatServerResponse* response) override;
  Status Login(ServerContext* context,
               const LoginRequest* request,
               LoginResponse* response) override;

private:
  void insertToken(int uid, std::string_view token);
  ChatServer getChatServer();
  std::string generatorUuid();

private:
  std::unordered_map<std::string, ChatServer> m_servers;
  std::unordered_map<int, std::string> m_tokens;
  std::mutex m_mtxServer;
  std::mutex m_mtxToken;
};

#endif // STATUSSERVERIMPL_H
