#ifndef LOGICSYSTEM_H
#define LOGICSYSTEM_H

#include "singleton.h"

#include <functional>
#include <unordered_map>

class HttpConnection;
using HttpConnectionPtr = std::shared_ptr<HttpConnection>;
using HttpHandler = std::function<void(const HttpConnectionPtr&)>;
using MapFunc = std::unordered_map<std::string, HttpHandler>;

class LogicSystem : public Singleton<LogicSystem>
{
  friend class Singleton<LogicSystem>;

public:
  ~LogicSystem() = default;

  bool handleGet(const std::string&, const HttpConnectionPtr&);
  void registGet(std::string_view, const HttpHandler&);
  void registPost(std::string_view, const HttpHandler&);
  bool handlePost(const std::string&, const HttpConnectionPtr&);

private:
  LogicSystem();

private:
  MapFunc m_postHandlers;
  MapFunc m_getHandlers;
};

#endif // LOGICSYSTEM_H
