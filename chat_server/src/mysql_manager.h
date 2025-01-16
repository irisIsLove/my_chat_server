#ifndef MYSQLMANAGER_H
#define MYSQLMANAGER_H

#include "mysql_dao.h"
#include "singleton.h"

class MysqlManager : public Singleton<MysqlManager>
{
  friend class Singleton<MysqlManager>;

public:
  ~MysqlManager() = default;

  int registerUser(std::string_view name,
                   std::string_view email,
                   std::string_view pass);
  bool checkEmail(std::string_view name, std::string_view email);
  bool updatePass(std::string_view name, std::string_view pass);
  bool checkPass(std::string_view email, std::string_view pass, UserInfo& user);
  UserInfoPtr getUser(std::string_view name);
  UserInfoPtr getUser(int uid);

private:
  MysqlManager() = default;

private:
  MysqlDao m_dao;
};

#endif // MYSQLMANAGER_H
