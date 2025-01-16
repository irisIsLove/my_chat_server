#ifndef GLOBAL_H
#define GLOBAL_H

#include <functional>

enum class ErrorCode
{
  SUCCESS,
  ERR_JSON,
  ERR_RPC,
  ERR_VARIFY_EXPIRED,
  ERR_VARIFY_CODE,
  ERR_USER_EXIST,
  ERR_PASS_ERR,
  ERR_EMAIL_NOT_MATCH,
  ERR_PASS_UP_FAIL,
  ERR_PASS_INVALID,
  ERR_UID_INVALID,
  ERR_TOKEN_INVALID,
};

class Defer
{
public:
  Defer(const std::function<void()>& func)
    : m_func(func)
  {
  }
  ~Defer() { m_func(); }

private:
  std::function<void()> m_func;
};

constexpr int MAX_POOL_SIZE = 5;
constexpr const char* CODE_PRIFIX = "code_";

#endif // GLOBAL_H
