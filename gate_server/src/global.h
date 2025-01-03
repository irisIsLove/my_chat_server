#ifndef GLOBAL_H
#define GLOBAL_H

enum class ErrorCode
{
  SUCCESS,
  ERR_JSON,
  ERR_RPC,
};

constexpr int MAX_RPC_SIZE = 5;

#endif // GLOBAL_H
