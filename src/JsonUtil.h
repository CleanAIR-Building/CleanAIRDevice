#pragma once
#include "Config.h"
#include "JsonDocuments.h"
#include <string>

namespace CleanAIR {
void ParseMessageJson(/*out*/ MessageJson& messageJson, /*in*/ const std::string& jsonString);
void ParseConfigJson(/*out*/ ConfigJson& configJson, /*in*/ const std::string& jsonString);
void ReadFileToString(/*out*/ std::string& fileString, /*in*/ const char* filename);
void LoadConfiguration(/*out*/ Config& config, /*in*/ const char* filename);
}  // namespace CleanAIR
