#include "message_node.h"
#include "global.h"

#include <boost/asio.hpp>

#include <cstring>

namespace net = boost::asio;

MessageNode::MessageNode(std::uint16_t maxLen)
  : m_curLen(0)
  , m_totalLen(maxLen)
{
  m_data = new char[m_totalLen + 1];
  m_data[m_totalLen] = '\0';
}

MessageNode::~MessageNode()
{
  delete[] m_data;
}

void
MessageNode::clear()
{
  std::memset(m_data, 0, m_totalLen);
  m_curLen = 0;
}

RecvNode::RecvNode(std::uint16_t maxLen, MessageID id)
  : MessageNode(maxLen)
  , m_id(id)
{
}

SendNode::SendNode(const char* message, std::uint16_t maxLen, MessageID id)
  : MessageNode(maxLen)
  , m_id(id)
{
  std::uint16_t msgIdHost = net::detail::socket_ops::host_to_network_short(
    static_cast<std::uint16_t>(m_id));
  std::memcpy(m_data, &msgIdHost, HEAD_ID_LEN);

  std::uint16_t msgLenHost =
    net::detail::socket_ops::host_to_network_short(maxLen);
  std::memcpy(m_data + HEAD_ID_LEN, &msgLenHost, HEAD_DATA_LEN);
  std::memcpy(m_data + HEAD_TOTAL_LEN, message, maxLen);
}
