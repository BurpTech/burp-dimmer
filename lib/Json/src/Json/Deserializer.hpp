#pragma once

#include <ArduinoJson.h>

namespace Json {
  class Deserializer {
    public:
      virtual void deserialize(const JsonObject & object) = 0;
  };
};
