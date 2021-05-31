#pragma once
#include "Arduino.h"
#include "ArduinoJson.h"
#include "Config.h"
#include "ESP8266WiFi.h"
#include "JsonDocuments.h"
#include "JsonUtil.h"
#include "MessageConsumer.h"
#include "MessageProducer.h"
#include "PubSubClient.h"
#include "Util.h"

namespace CleanAIR {

void LoadConfiguration(const char* filename);
void ConnectToWifi();
void ConnectToMQTT();
void ConnectToTopic();
void SetConsumer(MessageConsumer* newConsumer);
void SetProducer(MessageProducer* newProducer);
void Loop();
}  // namespace CleanAIR
