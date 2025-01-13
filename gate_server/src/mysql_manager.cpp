#include "mysql_manager.h"

int
MysqlManager::registerUser(std::string_view name,
                           std::string_view email,
                           std::string_view pass)
{
  return m_dao.registerUser(name, email, pass);
}

bool
MysqlManager::checkEmail(std::string_view name, std::string_view email)
{
  return m_dao.checkEmail(name, email);
}

bool
MysqlManager::updatePass(std::string_view name, std::string_view pass)
{
  return m_dao.updatePass(name, pass);
}

bool
MysqlManager::checkPass(std::string_view email,
                        std::string_view pass,
                        UserInfo& user)
{
  return m_dao.checkPass(email, pass, user);
}
