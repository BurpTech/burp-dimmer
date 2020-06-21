#pragma once

#include <ArduinoJson.h>
#include <functional>
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      using f_onState = std::function<void(const State::Instance * state)>;
      void deserialize(const JsonObject & object, f_onState onState);

    }
  }
}
