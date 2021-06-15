#include "CleanAIRDevice.h"
#include "Arduino.h"
#include "ArduinoJson.h"
#include "Config.h"
#include "ESP8266WiFi.h"
#include "HeartBeat.h"
#include "JsonDocuments.h"
#include "JsonUtil.h"
#include "MessageConsumer.h"
#include "MessageProducer.h"
#include "PubSubClient.h"
#include "TaskScheduler.h"
#include "Util.h"

namespace CleanAIR {

CleanAIR::Config config;
WiFiClient wifiClient;
PubSubClient pubSubClient;
TaskScheduler taskScheduler;
MessageConsumer* consumer;
MessageProducer* producer;
HeartBeat heartBeat;

const char* mqttClientName = "MQTT Client";

void ConnectToWifi(const Config& config) {
  Serial.print("Connect to Wifi ");
  WiFi.begin(config.ssid.c_str(), config.password.c_str());

  WaitFor([]() { return WiFi.status() == WL_CONNECTED; });

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void ConnectToMQTT(const Config& config, PubSubClient& pubSubClient, WiFiClient& wifiClient) {
  Serial.print("Connect to MQTT ");

  pubSubClient.setServer(config.mqttAddress.c_str(), config.mqttPort);
  pubSubClient.setClient(wifiClient);

  WaitFor([&config, &pubSubClient]() {
    return pubSubClient.connect(config.mqttClientName.c_str(), config.mqttUser.c_str(), config.mqttPassword.c_str());
  });
  Serial.println("MQTT connected");
}

void ConnectToTopic(const Config& config, PubSubClient& pubSubClient, MessageConsumer& consumer) {
  // Sets the callback that is used when a message arrives
  pubSubClient.setCallback([&consumer](char* topic, byte* payload, unsigned int length) {
    const std::string messageBody(reinterpret_cast<char*>(payload), length);
    Serial.printf("Topic: %s | Message body: %s\n", topic, messageBody.c_str());

    MessageJson messageJson;
    ParseMessageJson(messageJson, messageBody);
    consumer.Consume(topic, messageJson);
  });

  Serial.printf("Subscribing to topic: %s", config.mqttSubscribeTopic.c_str());
  WaitFor([&config, &pubSubClient]() { return pubSubClient.subscribe(config.mqttSubscribeTopic.c_str()); });
  Serial.printf("Subscribed to topic: %s\n", config.mqttSubscribeTopic.c_str());
}

void LoadConfiguration(/*out*/ Config& config, /*in*/ const char* filename) {
  std::string fileString;
  ReadFileToString(fileString, filename);

  ConfigJson configJson;
  ParseConfigJson(configJson, fileString);
  config.ssid = configJson["ssid"].as<const char*>();
  config.password = configJson["password"].as<const char*>();
  config.mqttAddress = configJson["mqttAddress"].as<const char*>();
  config.mqttPort = configJson["mqttPort"].as<uint16_t>();
  config.mqttUser = configJson["mqttUser"].as<const char*>();
  config.mqttPassword = configJson["mqttPassword"].as<const char*>();
  config.mqttPublishTopic = configJson["mqttPublishTopic"].as<const char*>();
  config.mqttSubscribeTopic = configJson["mqttSubscribeTopic"].as<const char*>();
  config.mqttClientName = configJson["mqttClientName"].as<const char*>();
  config.deviceType = configJson["deviceType"].as<const char*>();
}

void Loop() {
  if (WiFi.status() == WL_DISCONNECTED) {
    Serial.println("Lost connection to WiFI!");
    ConnectToWifi(config);
  }

  if (!pubSubClient.connected()) {
    Serial.println("Lost connection to MQTT!");
    ConnectToMQTT(config, pubSubClient, wifiClient);

    if (consumer) {
      ConnectToTopic(config, pubSubClient, *consumer);
    }
  }

  CleanAIR::pubSubClient.loop();
  if (consumer) {
    consumer->Loop();
  }
  if (producer) {
    producer->Loop();
  }
  taskScheduler.Loop();
}

void InitializeHeartBeat(HeartBeat& heartBeat, TaskScheduler& taskScheduler, PubSubClient& pubSubClient,
                         const Config& config, unsigned long interval = 5000) {
  heartBeat.SetDeviceName(config.mqttClientName);
  heartBeat.SetDeviceType(config.deviceType);
  heartBeat.SetPubSubClient(&pubSubClient);
  taskScheduler.AddTask(interval, [&heartBeat]() {
    heartBeat.Loop();
    return true;
  });
}

void LoadConfiguration(const char* filename) { LoadConfiguration(config, filename); }

void ConnectToWifi() { ConnectToWifi(config); }

void ConnectToMQTT() { ConnectToMQTT(config, pubSubClient, wifiClient); }

void ConnectToTopic() { ConnectToTopic(config, pubSubClient, *consumer); }

void SetConsumer(MessageConsumer* newConsumer) { consumer = newConsumer; }

void InitializeHeartBeat(unsigned long interval /*=5000*/) {
  InitializeHeartBeat(heartBeat, taskScheduler, pubSubClient, config, interval);
}

void SetProducer(MessageProducer* newProducer) {
  producer = newProducer;
  producer->SetPubSubClient(&pubSubClient);
}

const Config& GetConfig() { return config; }
}  // namespace CleanAIR
