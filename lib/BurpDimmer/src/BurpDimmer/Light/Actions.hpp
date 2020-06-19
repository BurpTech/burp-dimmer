#pragma once

#include <ArduinoJson.h>
#include <functional>
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    enum class Error {
      noError,
      noObject,
      maxLevels,
      outOfRange,
      invalidOn,
      invalidLevel,
      invalidPwm,
      maxBrightness,
      minBrightness
    };

    using f_onParams = std::function<void(const Error error, const Params * params)>;

    void deserialize(const JsonObject & object, f_onParams onParams);
    void applyConfig(const State * previous, f_onParams onParams);
    void toggle(const State * previous, f_onParams onParams);
    void increaseBrightness(const State * previous, f_onParams onParams);
    void decreaseBrightness(const State * previous, f_onParams onParams);

  }
}
