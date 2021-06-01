#include "CleanAIRDevice.h"
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

CleanAIR::Config config;
WiFiClient wifiClient;
PubSubClient pubSubClient;
MessageConsumer* consumer;
MessageProducer* producer;

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

  Serial.printf("Subscribing to topic: %s", config.mqttTopic.c_str());
  WaitFor([&config, &pubSubClient]() { return pubSubClient.subscribe(config.mqttTopic.c_str()); });
  Serial.printf("Subscribed to topic: %s\n", config.mqttTopic.c_str());
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
  config.mqttTopic = configJson["mqttTopic"].as<const char*>();
  config.mqttClientName = configJson["mqttClientName"].as<const char*>();
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
}

void LoadConfiguration(const char* filename) { LoadConfiguration(config, filename); }
void ConnectToWifi() { ConnectToWifi(config); }
void ConnectToMQTT() { ConnectToMQTT(config, pubSubClient, wifiClient); }
void ConnectToTopic() { ConnectToTopic(config, pubSubClient, *consumer); }
void SetConsumer(MessageConsumer* newConsumer) { consumer = newConsumer; }
void SetProducer(MessageProducer* newProducer) {
  producer = newProducer;
  producer->SetPubSubClient(&pubSubClient);
}
const Config& GetConfig() { return config; }
}  // namespace CleanAIR
