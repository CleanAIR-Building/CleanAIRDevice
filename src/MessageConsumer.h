#pragma once
#include "JsonDocuments.h"

namespace CleanAIR {
class MessageConsumer {
 public:
  virtual ~MessageConsumer() = default;
  virtual void Consume(const char* topic, const MessageJson& message) = 0;
};
}  // namespace CleanAIR
