#pragma once

#include <ArduinoJson.h>
#include <functional>
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      enum class Error {
        noError,
        noObject,
        noLevels,
        notAnArray,
        minLevels,
        maxLevels,
        invalidLevels,
        levelZero
      };

      using f_onLevels = std::function<void(const Error error, const Levels * levels)>;
      void deserialize(const JsonObject & object, f_onLevels onLevels);

      using f_onState = std::function<void(const State * state)>;
      void deserialize(const JsonObject & object, f_onState onState);

    }
  }
}
