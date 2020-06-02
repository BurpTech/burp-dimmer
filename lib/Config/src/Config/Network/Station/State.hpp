#pragma once

#include <ArduinoJson.h>
#include <Json/Serializer.hpp>
#include <Redux/State.hpp>

namespace Config {
  namespace Network {
    namespace Station {

      class State : public Json::Serializer, public Redux::State {
        public:

          State(const JsonObject & object);
          void serialize(JsonObject & object) const override;

      };

    }
  }
}
