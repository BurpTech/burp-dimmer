#pragma once

#include <ArduinoJson.h>

namespace Json {
  class Serializer {
    public:
      virtual void serialize(JsonObject & object) const = 0;
  };
};
