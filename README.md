# CleanAIRDevice

This is the library that is the basis for all sensors and actuators that are deployed on NodeMCUs. It provides the MQTT connection, configuration via json files, a heartbeat and timing utilities in a reusable way.

## Usage

Example from [traffic light](https://github.com/CleanAIR-Building/CleanAIR-actuator-traffic-light)

``` c++
#include "CleanAIRDevice.h"
#include "Definitions.h"
#include "TrafficLight.h"
#include "TrafficLightMessageProducer.h"

CleanAIR::TrafficLightMessageProducer trafficLightMessageProducer;
CleanAIR::TrafficLight trafficLight(&trafficLightMessageProducer, D1, D2);

void setup() {
  Serial.begin(BAUDRATE);
  CleanAIR::SetConsumer(&trafficLight);
  CleanAIR::SetProducer(&trafficLightMessageProducer);
  CleanAIR::LoadConfiguration(CONFIG_FILE);
  CleanAIR::ConnectToWifi();
  CleanAIR::ConnectToMQTT();
  CleanAIR::ConnectToTopic();
  CleanAIR::InitializeHeartBeat(HEARTBEAT);
}

void loop() { CleanAIR::Loop(); }
```

You have to place a config JSON under `data/Config.json`

```json
{
  "ssid": "the ssid",
  "password": "the psk",
  "mqttAddress": "the ip",
  "mqttPort": 1883,
  "mqttUser": "the user",
  "mqttPassword": "the users password",
  "mqttPublishTopic": "the topic you want to publish to",
  "mqttSubscribeTopic": "the topic you want to subscribe to",
  "mqttClientName": "The client name",
  "deviceType": "The device type"
}
```
