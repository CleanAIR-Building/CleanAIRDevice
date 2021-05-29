#pragma once
#include "ArduinoJson/Namespace.hpp"
#include <cstddef>

#define CONFIG_JSON_SIZE 512  /* TODO: More size than necessary. We should change that in the future.*/
#define MESSAGE_JSON_SIZE 128 /* TODO: More size than necessary. We should change that in the future.*/

namespace ARDUINOJSON_NAMESPACE {
template <size_t desiredCapacity>
class StaticJsonDocument;
}  // namespace ARDUINOJSON_NAMESPACE

namespace CleanAIR {
using MessageJson = ARDUINOJSON_NAMESPACE::StaticJsonDocument<MESSAGE_JSON_SIZE>;
using ConfigJson = ARDUINOJSON_NAMESPACE::StaticJsonDocument<CONFIG_JSON_SIZE>;
}  // namespace CleanAIR
