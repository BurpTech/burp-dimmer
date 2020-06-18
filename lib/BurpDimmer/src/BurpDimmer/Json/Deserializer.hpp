#pragma once

#include <ArduinoJson.h>

namespace BurpDimmer {
  namespace Json {

    class Deserializer {
      public:
        virtual void deserialize(const JsonObject & object) = 0;
    };

  }
}
