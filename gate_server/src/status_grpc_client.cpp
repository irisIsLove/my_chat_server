#include "status_grpc_client.h"
#include "config_manager.h"
#include "global.h"

#include <grpcpp/grpcpp.h>

GetChatServerResponse
StatusGrpcClient::getChatServer(int uid)
{
  grpc::ClientContext context;
  GetChatServerResponse response;
  GetChatServerRequest request;
  request.set_uid(uid);

  auto stub = m_pool->getConnection();
  Defer defer([this, &stub]() { m_pool->returnConnection(std::move(stub)); });
  Status status = stub->GetChatServer(&context, request, &response);
  if (!status.ok()) {
    response.set_error(static_cast<int>(ErrorCode::ERR_RPC));
  }
  return response;
}

StatusGrpcClient::StatusGrpcClient()
{
  auto& config = ConfigManager::getInstance();
  std::string host = config["StatusServer"]["host"];
  std::string port = config["StatusServer"]["port"];
  m_pool = std::make_unique<StatusConnectPool>(MAX_POOL_SIZE, host, port);
}

StatusConnectPool::StatusConnectPool(std::size_t poolSize,
                                     const std::string& host,
                                     const std::string& port)
{
  for (std::size_t i = 0; i < poolSize; ++i) {
    std::shared_ptr<Channel> channel = grpc::CreateChannel(
      host + ":" + port, grpc::InsecureChannelCredentials());
    m_stubs.emplace(std::move(StatusService::NewStub(channel)));
  }
}

StatusConnectPool::~StatusConnectPool()
{
  std::lock_guard<std::mutex> lock(m_mtx);
  close();
  while (!m_stubs.empty()) {
    m_stubs.pop();
  }
}

void
StatusConnectPool::close()
{
  m_stop = true;
  m_cond.notify_all();
}

std::unique_ptr<StatusService::Stub>
StatusConnectPool::getConnection()
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
StatusConnectPool::returnConnection(std::unique_ptr<StatusService::Stub> stub)
{
  std::lock_guard<std::mutex> lock(m_mtx);
  if (m_stop)
    return;

  m_stubs.emplace(std::move(stub));
  m_cond.notify_one();
}
