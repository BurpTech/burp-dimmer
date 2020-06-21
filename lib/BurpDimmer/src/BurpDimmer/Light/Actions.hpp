#pragma once

#include <ArduinoJson.h>
#include <functional>
#include "../Config/Light/State.hpp"
#include "State.hpp"
#include "Config.hpp"

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

    using f_onParams = std::function<void(const Error error, const State::Params * params)>;

    void deserialize(const JsonObject & object, const Config * config, f_onParams onParams);
    void applyConfig(const State::Instance * previous, const Config * config, f_onParams onParams);
    void toggle(const State::Instance * previous, const Config * config, f_onParams onParams);
    void increaseBrightness(const State::Instance * previous, const Config * config, f_onParams onParams);
    void decreaseBrightness(const State::Instance * previous, const Config * config, f_onParams onParams);

  }
}
