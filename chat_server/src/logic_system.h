#ifndef LOGICSYSTEM_H
#define LOGICSYSTEM_H

#include "chat_session.h"
#include "singleton.h"

#include <mutex>

using LogicCallBack =
  std::function<void(ChatSessionPtr, MessageID, std::string_view)>;
class LogicSystem : public Singleton<LogicSystem>
{
  friend class Singleton<LogicSystem>;

public:
  ~LogicSystem();
  void postMessageToQue(const LogicNodePtr& node);

private:
  LogicSystem();
  void registCallback();
  void dealMessage();
  void onLogin(ChatSessionPtr, MessageID id, std::string_view data);

private:
  std::thread m_worker;
  std::mutex m_mtx;
  std::condition_variable m_cond;
  std::queue<LogicNodePtr> m_queMesssage;
  bool m_isStop = false;
  std::unordered_map<MessageID, LogicCallBack> m_callbacks;
};

#endif // LOGICSYSTEM_H
