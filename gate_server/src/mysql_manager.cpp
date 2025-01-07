#include "mysql_manager.h"

int
MysqlManager::registerUser(std::string_view name,
                           std::string_view email,
                           std::string_view pass)
{
  return m_dao.registerUser(name, email, pass);
}