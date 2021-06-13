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
  void Publish(const char* topic, const MessageJson& message, boolean retained = false);

 private:
  PubSubClient* mPubSubClient;
};
}  // namespace CleanAIR
