#pragma once

#include <ArduinoJson.h>
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {

    using f_onState = std::function<void(const State * state)>;
    void deserialize(const JsonObject & object, f_onState onState);

  }
}
