#include "Arduino.h"
#include "ArduinoJson.h"
#include "Config.h"
#include "ESP8266WiFi.h"
#include "JsonDocuments.h"
#include "JsonUtil.h"
#include "MessageConsumer.h"
#include "PubSubClient.h"
#include "Util.h"

namespace CleanAIR {

void LoadConfiguration(const char* filename);
void ConnectToWifi();
void ConnectToMQTT();
void SetConsumer(MessageConsumer* consumer);
void SetMQTTClientName(const char* newMqttClientName);
void Loop();
}  // namespace CleanAIR
