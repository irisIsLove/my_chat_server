#include "varify_grpc_client.h"
#include "config_manager.h"
#include "global.h"

RpcConnectPool::RpcConnectPool(std::size_t poolSize,
                               const std::string& host,
                               const std::string& port)
{
  for (std::size_t i = 0; i < poolSize; ++i) {
    std::shared_ptr<Channel> channel = grpc::CreateChannel(
      std::string(host + ':' + port), grpc::InsecureChannelCredentials());
    m_stubs.emplace(VarifyService::NewStub(channel));
  }
}

RpcConnectPool::~RpcConnectPool()
{
  std::lock_guard<std::mutex> lock(m_mtx);
  close();
  while (!m_stubs.empty()) {
    m_stubs.pop();
  }
}

void
RpcConnectPool::close()
{
  m_stop = true;
  m_cond.notify_all();
}

std::unique_ptr<VarifyService::Stub>
RpcConnectPool::getConnection()
{
  std::unique_lock<std::mutex> lock(m_mtx);
  m_cond.wait(lock, [this]() {
    if (m_stop)
      return true;
    return !m_stubs.empty();
  });
  if (m_stop)
    return nullptr;

  auto stub = std::move(m_stubs.front());
  m_stubs.pop();
  return stub;
}

void
RpcConnectPool::returnConnection(std::unique_ptr<VarifyService::Stub> stub)
{
  std::lock_guard<std::mutex> lock(m_mtx);
  if (m_stop)
    return;

  m_stubs.push(std::move(stub));
  m_cond.notify_one();
}

message::GetVarifyResponse
VarifyGrpcClient::getVarifyCode(std::string_view email)
{
  ClientContext context;
  GetVarifyResponse reply;
  GetVarifyRequest request;
  request.set_email(email);

  auto stub = m_pool->getConnection();
  Status status = stub->GetVarifyCode(&context, request, &reply);
  if (!status.ok()) {
    reply.set_error(static_cast<int>(ErrorCode::ERR_RPC));
  }
  m_pool->returnConnection(std::move(stub));

  return reply;
}

VarifyGrpcClient::VarifyGrpcClient()
{
  auto& config = ConfigManager::getInstance();
  auto host = config["VarifyServer"]["host"];
  auto port = config["VarifyServer"]["port"];
  m_pool = std::make_unique<RpcConnectPool>(MAX_POOL_SIZE, host, port);
}
