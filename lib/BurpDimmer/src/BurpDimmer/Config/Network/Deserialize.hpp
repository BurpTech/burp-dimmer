#pragma once

#include <ArduinoJson.h>
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      using f_onState = std::function<void(const State * state)>;
      void deserialize(const JsonObject & object, f_onState onState);

    }
  }
}
