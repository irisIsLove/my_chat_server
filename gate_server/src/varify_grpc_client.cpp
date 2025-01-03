#include "varify_grpc_client.h"
#include "global.h"

message::GetVarifyResponse
VarifyGrpcClient::getVarifyCode(std::string_view email)
{
  ClientContext context;
  GetVarifyResponse reply;
  GetVarifyRequest request;
  request.set_email(email);

  Status status = m_stub->GetVarifyCode(&context, request, &reply);
  if (!status.ok()) {
    reply.set_error(static_cast<int>(ErrorCode::ERR_RPC));
  }
  return reply;
}

VarifyGrpcClient::VarifyGrpcClient()
{
  std::shared_ptr<Channel> channel =
    grpc::CreateChannel("127.0.0.1:8081", grpc::InsecureChannelCredentials());
  m_stub = VarifyService::NewStub(channel);
}
