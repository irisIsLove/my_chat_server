#ifndef VARIFYGRPCCLIENT_H
#define VARIFYGRPCCLIENT_H

#include "messages/message.grpc.pb.h"
#include "singleton.h"

#include <grpcpp/grpcpp.h>

class VarifyGrpcClient : public Singleton<VarifyGrpcClient>
{
  using Channel = grpc::Channel;
  using Status = grpc::Status;
  using ClientContext = grpc::ClientContext;
  using GetVarifyRequest = message::GetVarifyRequest;
  using GetVarifyResponse = message::GetVarifyResponse;
  using VarifyService = message::VarifyService;

  friend class Singleton<VarifyGrpcClient>;

public:
  GetVarifyResponse getVarifyCode(std::string_view email);

private:
  VarifyGrpcClient();

private:
  std::unique_ptr<VarifyService::Stub> m_stub;
};

#endif // VARIFYGRPCCLIENT_H
