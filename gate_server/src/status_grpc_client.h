#ifndef STATUSGRPCCLIENT_H
#define STATUSGRPCCLIENT_H

#include "messages/message.grpc.pb.h"

#include <queue>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using message::GetChatServerRequest;
using message::GetChatServerResponse;
using message::LoginRequest;
using message::LoginResponse;
using message::StatusService;

class StatusConnectPool
{
  using StubQueue = std::queue<std::unique_ptr<StatusService::Stub>>;

public:
  StatusConnectPool(std::size_t poolSize,
                    const std::string& host,
                    const std::string& port);
  ~StatusConnectPool();
};

class StatusGrpcClient
{
public:
  StatusGrpcClient();

private:
};

#endif // STATUSGRPCCLIENT_H
