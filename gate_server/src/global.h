#ifndef GLOBAL_H
#define GLOBAL_H

enum class ErrorCode
{
  SUCCESS,
  ERR_JSON,
  ERR_RPC,
};

class ConfigManager;
extern ConfigManager ConfigManager;

#endif // GLOBAL_H
