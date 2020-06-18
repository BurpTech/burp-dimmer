#pragma once

#include <ArduinoJson.h>

namespace BurpDimmer {
  namespace Json {

    class Document {
      public:
        virtual void serialize(JsonDocument & doc) = 0;
        virtual void deserialize(JsonDocument & doc) = 0;
    };

  }
}
