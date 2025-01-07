#ifndef GLOBAL_H
#define GLOBAL_H

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

constexpr int MAX_POOL_SIZE = 5;
constexpr const char* CODE_PRIFIX = "code_";

#endif // GLOBAL_H
