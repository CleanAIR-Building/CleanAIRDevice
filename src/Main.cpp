#include "Arduino.h"
#include "CleanAIRDevice.h"

void setup() {
  Serial.begin(115200);
  CleanAIR::ConnectToWifi();
  CleanAIR::ConnectToMQTT();
}

void loop() { CleanAIR::Loop(); }
