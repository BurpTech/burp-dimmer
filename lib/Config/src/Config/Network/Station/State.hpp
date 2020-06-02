#pragma once

#include <ArduinoJson.h>
#include <Json/Serializer.hpp>

namespace Config {
  namespace Network {
    namespace Station {

      class State : public Json::Serializer {
        public:

          State(const JsonObject & object);
          void serialize(JsonObject & object) const override;

      };

    }
  }
}
