#pragma once
#include "JsonDocuments.h"
#include <string>

class PubSubClient;

namespace CleanAIR {
class MessageProducer {
 public:
  virtual ~MessageProducer() = default;
  virtual void Loop() = 0;
  void SetPubSubClient(PubSubClient* newPubSubClient);

 protected:
  void Publish(const char* topic, const MessageJson& message);
  void Publish(const char* topic, const MessageJson& message, boolean retained);

 private:
  PubSubClient* mPubSubClient;
};
}  // namespace CleanAIR
