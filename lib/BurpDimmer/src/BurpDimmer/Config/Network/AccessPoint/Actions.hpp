#pragma once

#include <ArduinoJson.h>
#include <functional>
#include <BurpRedux/Action/Instance.hpp>
#include "../../ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        enum class Error {
          noError,
          noObject,
          noTest,
          invalidTest
        };

        using Action = BurpRedux::Action::Instance<State::Params, ActionType::NETWORK_ACCESS_POINT_SET_STATE>;
        using f_onParams = std::function<void(const Error error, const State::Params * params)>;
        void deserialize(const JsonObject & object, f_onParams onParams);

      }
    }
  }
}
