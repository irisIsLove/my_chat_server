#ifndef MESSAGENODE_H
#define MESSAGENODE_H

#include "global.h"

#include <cstdint>
#include <memory>

struct MessageNode
{
  MessageNode(std::uint16_t maxLen);
  virtual ~MessageNode();
  void clear();

  std::uint16_t m_curLen;
  std::uint16_t m_totalLen;
  char* m_data = nullptr;
};
using MessageNodePtr = std::shared_ptr<MessageNode>;

struct RecvNode : public MessageNode
{
  RecvNode(std::uint16_t maxLen, MessageID id);

  MessageID m_id;
};
using RecvNodePtr = std::shared_ptr<RecvNode>;

struct SendNode : public MessageNode
{
  SendNode(const char* message, std::uint16_t maxLen, MessageID id);

  MessageID m_id;
};
using SendNodePtr = std::shared_ptr<SendNode>;

#endif // MESSAGENODE_H
