#include "Util.h"
#include "Arduino.h"

namespace CleanAIR {
void WaitFor(std::function<bool()> expression) {
  while (!expression()) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
}
}  // namespace CleanAIR
