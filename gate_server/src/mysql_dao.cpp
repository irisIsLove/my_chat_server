#include "mysql_dao.h"
#include "config_manager.h"
#include "global.h"

#include <fmt/printf.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/mysql_driver.h>

using SqlPrepareStmtPtr = std::unique_ptr<sql::PreparedStatement>;
using SqlStatementPtr = std::unique_ptr<sql::Statement>;
using SqlResultSetPtr = std::unique_ptr<sql::ResultSet>;

SqlConnection::SqlConnection(sql::Connection* con, std::int64_t lastOperTime)
  : m_con(con)
  , m_lastOperTime(lastOperTime)
{
}

MysqlPool::MysqlPool(std::string_view url,
                     std::string_view user,
                     std::string_view pass,
                     std::string_view schema,
                     int poolSize)
  : m_url(url)
  , m_user(user)
  , m_pass(pass)
  , m_schema(schema)
{
  try {
    for (int i = 0; i < poolSize; ++i) {
      sql::mysql::MySQL_Driver* driver =
        sql::mysql::get_mysql_driver_instance();
      auto con = driver->connect(url.data(), user.data(), pass.data());
      con->setSchema(schema.data());
      auto currentTime = std::chrono::system_clock::now().time_since_epoch();
      auto timeStamp =
        std::chrono::duration_cast<std::chrono::milliseconds>(currentTime)
          .count();

      m_pool.emplace(std::make_unique<SqlConnection>(con, timeStamp));
    }

    m_threadCheck = std::thread([this]() {
      while (m_isStop) {
        checkConnection();
        std::this_thread::sleep_for(std::chrono::seconds(60));
      }
    });
    m_threadCheck.detach();
  } catch (sql::SQLException& e) {
    fmt::println("Mysql pool init failed, error is {}", e.what());
  }
}

void
MysqlPool::checkConnection()
{
  std::lock_guard<std::mutex> lock(m_mtx);
  auto currentTime = std::chrono::system_clock::now().time_since_epoch();
  auto timeStamp =
    std::chrono::duration_cast<std::chrono::milliseconds>(currentTime).count();
  int poolSize = m_pool.size();
  for (int i = 0; i < poolSize; ++i) {
    auto con = std::move(m_pool.front());
    m_pool.pop();
    Defer defer([this, &con]() { m_pool.push(std::move(con)); });

    if (timeStamp - con->m_lastOperTime < 5)
      continue;

    try {
      std::unique_ptr<sql::Statement> stmt(con->m_con->createStatement());
      stmt->executeQuery("SELECT 1");
      con->m_lastOperTime = timeStamp;
    } catch (sql::SQLException& e) {
      fmt::println("Error keeping connection alive: {}", e.what());
      auto driver = sql::mysql::get_driver_instance();
      auto newCon = driver->connect(m_url.data(), m_user.data(), m_pass.data());
      newCon->setSchema(m_schema.data());
      con->m_con.reset(newCon);
      con->m_lastOperTime = timeStamp;
    }
  }
}

SqlConnectionPtr
MysqlPool::getConnection()
{
  std::unique_lock<std::mutex> lock(m_mtx);
  m_cond.wait(lock, [this]() {
    if (m_isStop)
      return true;

    return !m_pool.empty();
  });

  if (m_isStop)
    return nullptr;

  auto con = std::move(m_pool.front());
  m_pool.pop();
  return con;
}

void
MysqlPool::returnConnection(SqlConnectionPtr con)
{
  std::lock_guard<std::mutex> lock(m_mtx);
  if (m_isStop)
    return;

  m_pool.push(std::move(con));
  m_cond.notify_one();
}

void
MysqlPool::close()
{
  m_isStop = true;
  m_cond.notify_all();
}

MysqlPool::~MysqlPool()
{
  std::lock_guard<std::mutex> lock(m_mtx);
  while (!m_pool.empty()) {
    m_pool.front()->m_con->close();
    m_pool.pop();
  }
}

MysqlDao::MysqlDao()
{
  auto& config = ConfigManager::getInstance();
  auto host = config["Mysql"]["host"];
  auto port = config["Mysql"]["port"];
  auto user = config["Mysql"]["user"];
  auto pass = config["Mysql"]["pass"];
  auto schema = config["Mysql"]["schema"];
  m_pool = std::make_unique<MysqlPool>(
    host + ":" + port, user, pass, schema, MAX_POOL_SIZE);
}

MysqlDao::~MysqlDao()
{
  m_pool->close();
}

int
MysqlDao::registerUser(std::string_view name,
                       std::string_view email,
                       std::string_view pass)
{
  auto con = m_pool->getConnection();
  Defer defer([this, &con]() { m_pool->returnConnection(std::move(con)); });
  try {
    if (con == nullptr)
      return 0;

    SqlPrepareStmtPtr stmt(
      con->m_con->prepareStatement("CALL reg_user(?, ?, ?, @result)"));

    stmt->setString(1, name.data());
    stmt->setString(2, email.data());
    stmt->setString(3, pass.data());
    stmt->execute();

    SqlStatementPtr stmtResult(con->m_con->createStatement());

    SqlResultSetPtr resultSet(
      stmtResult->executeQuery("SELECT @result AS result"));
    if (resultSet->next()) {
      int result = resultSet->getInt("result");
      fmt::println("Result: {}", result);
      return result;
    }
  } catch (sql::SQLException& e) {
    fmt::println("SQLException: {}", e.what());
    fmt::println("(MySQL error code: {}, SQLState: {})",
                 e.getErrorCode(),
                 e.getSQLState());
  }
  return -1;
}

bool
MysqlDao::checkEmail(std::string_view name, std::string_view email)
{
  auto con = m_pool->getConnection();
  Defer defer([this, &con]() { m_pool->returnConnection(std::move(con)); });
  try {
    if (con == nullptr)
      return false;

    SqlPrepareStmtPtr stmt(
      con->m_con->prepareStatement("SELECT email FROM user where name = ?"));
    stmt->setString(1, name.data());

    SqlResultSetPtr resultSet(stmt->executeQuery());
    while (resultSet->next()) {
      fmt::println("Check email: {}", email);
      if (std::string(email) != resultSet->getString("email"))
        return false;
      return true;
    }
  } catch (sql::SQLException& e) {
    fmt::println("SQLException: {}", e.what());
    fmt::println("(MySQL error code: {}, SQLState: {})",
                 e.getErrorCode(),
                 e.getSQLState());
  }
  return false;
}

bool
MysqlDao::updatePass(std::string_view name, std::string_view newPass)
{
  auto con = m_pool->getConnection();
  Defer defer([this, &con]() { m_pool->returnConnection(std::move(con)); });
  try {
    if (con == nullptr)
      return false;

    SqlPrepareStmtPtr stmt(
      con->m_con->prepareStatement("UPDATE user SET pwd = ? WHERE name = ?"));
    stmt->setString(1, newPass.data());
    stmt->setString(2, name.data());

    int updateCount = stmt->executeUpdate();
    fmt::println("Update count: {}", updateCount);
    return updateCount > 0;
  } catch (sql::SQLException& e) {
    fmt::println("SQLException: {}", e.what());
    fmt::println("(MySQL error code: {}, SQLState: {})",
                 e.getErrorCode(),
                 e.getSQLState());
  }
  return false;
}

bool
MysqlDao::checkPass(std::string_view email,
                    std::string_view pass,
                    UserInfo& user)
{
  auto con = m_pool->getConnection();
  if (con == nullptr)
    return false;

  Defer defer([this, &con]() { m_pool->returnConnection(std::move(con)); });
  try {
    SqlPrepareStmtPtr stmt(
      con->m_con->prepareStatement("SELECT * FROM user where email = ?"));
    stmt->setString(1, email.data());

    SqlResultSetPtr result(stmt->executeQuery());
    std::string originPass = "";

    while (result->next()) {
      originPass = result->getString("pwd");
      fmt::println("Origin pass: {}", originPass);
      break;
    }

    if (pass != originPass)
      return false;

    user.name = result->getString("name");
    user.email = email;
    user.uid = result->getInt("uid");
    user.pass = originPass;
    return true;
  } catch (sql::SQLException& e) {
    fmt::println("SQLException: {}", e.what());
    fmt::println("(MySQL error code: {}, SQLState: {})",
                 e.getErrorCode(),
                 e.getSQLState());
  }
  return false;
}
