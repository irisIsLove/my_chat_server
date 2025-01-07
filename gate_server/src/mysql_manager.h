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

private:
  MysqlManager() = default;

private:
  MysqlDao m_dao;
};

#endif // MYSQLMANAGER_H
