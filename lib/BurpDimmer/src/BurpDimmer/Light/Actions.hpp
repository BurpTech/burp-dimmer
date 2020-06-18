#pragma once

#include <ArduinoJson.h>
#include <functional>
#include "ActionType.hpp"

namespace BurpDimmer {
  namespace Light {
    namespace Actions {

      enum class Error {
        noError,
        noObject,
        outOfRange,
        invalidOn,
        invalidLevel,
        invalidPwm,
        maxBrightness,
        minBrightness
      };

      using f_onState = Light::f_onState<Error, State>;
      using action = Light::action<Error, State, ActionType::LIGHT_SET_CONFIG>;

      void deserialize(const JsonObject & object, f_onState onState);
      void applyConfig(const State & previous, f_onState onState);
      void toggle(const State & previous, f_onState onState);
      void increaseBrightness(const State & previous, f_onState onState);
      void decreaseBrightness(const State & previous, f_onState onState);

    }
  }
}
