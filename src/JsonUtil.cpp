#include "JsonUtil.h"
#include "Arduino.h"
#include "ArduinoJson.h"
#include "LittleFS.h"
#include <string>

namespace CleanAIR {
template <class T>
void ParseJsonDocument(/*out*/ T& document, /*in*/ const std::string& jsonString) {
  DeserializationError error = deserializeJson(document, jsonString);
  if (error) {
    Serial.println(F("Failed to read string!"));
  }
}

void ParseMessageJson(/*out*/ MessageJson& messageJson, /*in*/ const std::string& jsonString) {
  ParseJsonDocument(messageJson, jsonString);
}

void ParseConfigJson(/*out*/ ConfigJson& configJson, /*in*/ const std::string& jsonString) {
  ParseJsonDocument(configJson, jsonString);
}

void ReadFileToString(/*out*/ std::string& fileString, /*in*/ const char* filename) {
  LittleFSConfig cfg;
  cfg.setAutoFormat(false);
  LittleFS.setConfig(cfg);
  LittleFS.begin();

  File file = LittleFS.open(filename, "r");
  if (!file) {
    Serial.println("file open failed");
  }

  while (file.available()) {
    fileString += static_cast<char>(file.read());
  }
  file.close();
  LittleFS.end();
}
}  // namespace CleanAIR
