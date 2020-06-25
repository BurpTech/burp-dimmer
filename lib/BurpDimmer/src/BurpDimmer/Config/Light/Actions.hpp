#pragma once

#include <ArduinoJson.h>
#include <functional>
#include <BurpRedux/Action/Instance.hpp>
#include "../ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      enum class Error {
        noError,
        noObject,
        noLevels,
        noSaveStateDelay,
        noOffLevel,
        notAnArray,
        minLevels,
        maxLevels,
        invalidLevels,
        invalidSaveStateDelay,
        invalidOffLevel,
        offLevelOutOfRange,
        levelZero
      };

      using Action = BurpRedux::Action::Instance<State::Params, ActionType::LIGHT_SET_STATE>;
      using f_onParams = std::function<void(const Error error, const State::Params * params)>;
      void deserialize(const JsonObject & object, f_onParams onParams);

    }
  }
}
