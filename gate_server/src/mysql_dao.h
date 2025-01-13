#ifndef MYSQLDAO_H
#define MYSQLDAO_H

#include <jdbc/mysql_connection.h>

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

struct SqlConnection
{
  SqlConnection(sql::Connection* con, std::int64_t lastOperTime);
  std::unique_ptr<sql::Connection> m_con;
  std::int64_t m_lastOperTime;
};
using SqlConnectionPtr = std::unique_ptr<SqlConnection>;

class MysqlPool
{

public:
  MysqlPool(std::string_view url,
            std::string_view user,
            std::string_view pass,
            std::string_view schema,
            int poolSize);
  ~MysqlPool();

  void checkConnection();
  SqlConnectionPtr getConnection();
  void returnConnection(SqlConnectionPtr con);
  void close();

private:
  std::string m_url;
  std::string m_user;
  std::string m_pass;
  std::string m_schema;
  std::atomic<bool> m_isStop = false;
  std::mutex m_mtx;
  std::condition_variable m_cond;
  std::thread m_threadCheck;
  std::queue<SqlConnectionPtr> m_pool;
};
using MysqlPoolPtr = std::unique_ptr<MysqlPool>;

class MysqlDao
{
public:
  MysqlDao();
  ~MysqlDao();

  int registerUser(std::string_view name,
                   std::string_view email,
                   std::string_view pass);
  bool checkEmail(std::string_view name, std::string_view email);
  bool updatePass(std::string_view name, std::string_view newPass);

private:
  MysqlPoolPtr m_pool;
};

#endif // MYSQLDAO_H
