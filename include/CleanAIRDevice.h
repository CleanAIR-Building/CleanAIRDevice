#pragma once
#include "MessageConsumer.h"

namespace CleanAIR {

void LoadConfiguration(const char* filename);
void ConnectToWifi();
void ConnectToMQTT();
void SetConsumer(MessageConsumer* consumer);
void Loop();
}  // namespace CleanAIR
