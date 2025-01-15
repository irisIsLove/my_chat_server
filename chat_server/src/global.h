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
};

enum class MessageID
{
  MSG_CHAT_LOGIN,
  MSG_CHAT_LOGIN_RSP,
  ID_SEARCH_USER_REQ,
  ID_SEARCH_USER_RSP,
  ID_ADD_FRIEND_REQ,
  ID_ADD_FRIEND_RSP,
  ID_NOTIFY_ADD_FRIEND_REQ,
  ID_AUTH_FRIEND_REQ,
  ID_AUTH_FRIEND_RSP,
  ID_NOTIFY_AUTH_FRIEND_REQ,
  MESSAGE_ID_VALID,
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
constexpr int HEAD_TOTAL_LEN = 4;
constexpr int HEAD_ID_LEN = 2;
constexpr int HEAD_DATA_LEN = 2;
constexpr int MAX_LENGTH = 1024 * 2;
constexpr int MAX_SEND_QUEUE = 1000;
constexpr int MAX_RECV_QUEUE = 1000;

constexpr const char* CODE_PRIFIX = "code_";

#endif // GLOBAL_H
