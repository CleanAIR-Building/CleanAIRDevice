#include "HeartBeat.h"
#include "ArduinoJson.h"
#include "JsonDocuments.h"

namespace CleanAIR {
void HeartBeat::SetDeviceName(const std::string& name) { mName = name; }
void HeartBeat::SetDeviceType(const std::string& type) { mType = type; }
void HeartBeat::Loop() {
  CleanAIR::MessageJson heartBeat;
  heartBeat["name"] = mName.c_str();
  heartBeat["type"] = mType.c_str();
  Publish("heartbeat", heartBeat);
}
}  // namespace CleanAIR
