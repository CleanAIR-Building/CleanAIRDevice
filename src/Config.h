#pragma once
#include <stdint.h>
#include <string>

namespace CleanAIR {
struct Config {
  std::string ssid;
  std::string password;
  std::string mqttAddress;
  uint16_t mqttPort;
  std::string mqttUser;
  std::string mqttPassword;
  std::string mqttTopic;
  std::string mqttClientName;
  std::string deviceType;
};
}  // namespace CleanAIR
