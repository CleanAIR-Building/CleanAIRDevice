#include "MessageProducer.h"
#include "ArduinoJson.h"
#include "JsonDocuments.h"
#include "PubSubClient.h"

namespace CleanAIR {
void MessageProducer::SetPubSubClient(PubSubClient* newPubSubClient) { mPubSubClient = newPubSubClient; }

void MessageProducer::Publish(const char* topic, const MessageJson& message, boolean retained /*= false*/) {
  char messageBuffer[MESSAGE_JSON_SIZE];
  serializeJson(message, messageBuffer);
  mPubSubClient->publish(topic, messageBuffer, retained);
}
}  // namespace CleanAIR
