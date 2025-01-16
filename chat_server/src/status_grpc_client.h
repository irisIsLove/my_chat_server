#ifndef STATUSGRPCCLIENT_H
#define STATUSGRPCCLIENT_H

#include "messages/message.grpc.pb.h"
#include "singleton.h"

#include <condition_variable>
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

  void close();
  std::unique_ptr<StatusService::Stub> getConnection();
  void returnConnection(std::unique_ptr<StatusService::Stub> stub);

private:
  std::atomic<bool> m_stop = false;
  StubQueue m_stubs;
  std::condition_variable m_cond;
  std::mutex m_mtx;
};

class StatusGrpcClient : public Singleton<StatusGrpcClient>
{
  friend class Singleton<StatusGrpcClient>;

public:
  GetChatServerResponse getChatServer(int uid);
  LoginResponse login(int uid, std::string_view token);

private:
  StatusGrpcClient();

private:
  std::unique_ptr<StatusConnectPool> m_pool;
};

#endif // STATUSGRPCCLIENT_H
