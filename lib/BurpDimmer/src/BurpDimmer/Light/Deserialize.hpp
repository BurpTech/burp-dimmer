#pragma once

#include <ArduinoJson.h>
#include <functional>
#include "Config.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    using f_onState = std::function<void(const State::Instance * state)>;
    void deserialize(State::Creator & creator, const JsonObject & object, const Config * config, f_onState onState);

  }
}
