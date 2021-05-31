#pragma once
#include "JsonDocuments.h"

namespace CleanAIR {
class Messenger {
 public:
  virtual ~Messenger() = default;
  virtual void Consume(const char* topic, const MessageJson& message) = 0;
  virtual void Loop() = 0;
};
}  // namespace CleanAIR
