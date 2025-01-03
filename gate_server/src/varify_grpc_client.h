#ifndef VARIFYGRPCCLIENT_H
#define VARIFYGRPCCLIENT_H

#include "messages/message.grpc.pb.h"
#include "singleton.h"

#include <grpcpp/grpcpp.h>

#include <condition_variable>
#include <queue>

using Channel = grpc::Channel;
using Status = grpc::Status;
using ClientContext = grpc::ClientContext;
using GetVarifyRequest = message::GetVarifyRequest;
using GetVarifyResponse = message::GetVarifyResponse;
using VarifyService = message::VarifyService;

class RpcConnectPool
{
  using StubQueue = std::queue<std::unique_ptr<VarifyService::Stub>>;

public:
  RpcConnectPool(std::size_t poolSize,
                 const std::string& host,
                 const std::string& port);
  ~RpcConnectPool();

  void close();
  std::unique_ptr<VarifyService::Stub> getConnection();
  void returnConnection(std::unique_ptr<VarifyService::Stub> stub);

private:
  std::atomic<bool> m_stop = false;
  StubQueue m_queStub;
  std::condition_variable m_cond;
  std::mutex m_mtx;
};

class VarifyGrpcClient : public Singleton<VarifyGrpcClient>
{

  friend class Singleton<VarifyGrpcClient>;

public:
  GetVarifyResponse getVarifyCode(std::string_view email);

private:
  VarifyGrpcClient();

private:
  std::unique_ptr<RpcConnectPool> m_pool;
};

#endif // VARIFYGRPCCLIENT_H
