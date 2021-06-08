#pragma once
#include "MessageProducer.h"
#include <string>

namespace CleanAIR {
class HeartBeat : public MessageProducer {
 public:
  void SetDeviceName(const std::string& name);
  void SetDeviceType(const std::string& type);
  void Loop() override;

 private:
  std::string mName;
  std::string mType;
};
}  // namespace CleanAIR
