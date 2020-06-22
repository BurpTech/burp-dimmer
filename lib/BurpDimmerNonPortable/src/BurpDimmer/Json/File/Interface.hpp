#pragma once

#include <ArduinoJson.h>

namespace BurpDimmer {
  namespace Json {
    namespace File {

      class Interface {

        public:

          virtual void read(JsonDocument & doc) const = 0;
          virtual void write(JsonDocument & doc) const = 0;
          virtual void remove() = 0;

      };

    }
  }
}
