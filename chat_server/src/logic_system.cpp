#include "logic_system.h"

#include <fmt/printf.h>
#include <json/json.h>

LogicSystem::~LogicSystem() {}

void
LogicSystem::postMessageToQue(const LogicNodePtr& node)
{
  std::unique_lock<std::mutex> lock(m_mtx);
  m_queMesssage.emplace(node);
  if (m_queMesssage.size() == 1) {
    lock.unlock();
    m_cond.notify_one();
  }
}

LogicSystem::LogicSystem()
{
  registCallback();
  m_worker = std::thread(&LogicSystem::dealMessage, this);
}

void
LogicSystem::registCallback()
{
  m_callbacks[MessageID::MSG_CHAT_LOGIN] = std::bind(&LogicSystem::onLogin,
                                                     this,
                                                     std::placeholders::_1,
                                                     std::placeholders::_2,
                                                     std::placeholders::_3);
}

void
LogicSystem::dealMessage()
{
  for (;;) {
    std::unique_lock<std::mutex> lock(m_mtx);
    while (m_queMesssage.empty() || !m_isStop) {
      m_cond.wait(lock);
    }

    if (m_isStop) {
      while (!m_queMesssage.empty()) {
        auto& message = m_queMesssage.front();
        fmt::println("[LogicSystem::dealMessage] RecvMessage id: {}",
                     static_cast<int>(message->m_recvNode->m_id));
        auto iter = m_callbacks.find(message->m_recvNode->m_id);
        if (iter == m_callbacks.end()) {
          m_queMesssage.pop();
          continue;
        }

        iter->second(message->m_session,
                     message->m_recvNode->m_id,
                     message->m_recvNode->m_data);
        m_queMesssage.pop();
      }
      break;
    }

    auto& message = m_queMesssage.front();
    fmt::println("[LogicSystem::dealMessage] RecvMessage id: {}",
                 static_cast<int>(message->m_recvNode->m_id));
    auto iter = m_callbacks.find(message->m_recvNode->m_id);
    if (iter == m_callbacks.end()) {
      m_queMesssage.pop();
      fmt::println(
        "[LogicSystem::dealMessage] RecvMessage id [{}] handler not found",
        static_cast<int>(message->m_recvNode->m_id));
      continue;
    }
    iter->second(message->m_session,
                 message->m_recvNode->m_id,
                 message->m_recvNode->m_data);
    m_queMesssage.pop();
  }
}

void
LogicSystem::onLogin(ChatSessionPtr session,
                     MessageID id,
                     std::string_view data)
{
  Json::Reader reader;
  Json::Value root;
  reader.parse(data.data(), root);
  fmt::println("[LogicSystem::onLogin] User login uid is {} user token is {}",
               root["uid"].asInt(),
               root["token"].asString());

  session->send(root.toStyledString(), id);
}
