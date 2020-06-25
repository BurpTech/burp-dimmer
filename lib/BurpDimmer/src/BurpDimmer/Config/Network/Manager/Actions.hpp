#pragma once

#include <ArduinoJson.h>
#include <functional>
#include <BurpRedux/Action/Instance.hpp>
#include "../../ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        enum class Error {
          noError,
          noObject,
          noMode,
          noAccessPointTimeout,
          invalidMode,
          invalidAccessPointTimeout,
          unknownMode
        };

        using Action = BurpRedux::Action::Instance<State::Params, ActionType::NETWORK_MANAGER_SET_STATE>;
        using f_onParams = std::function<void(const Error error, const State::Params * params)>;
        void deserialize(const JsonObject & object, f_onParams onParams);
        void nextPermMode(const State::Instance * previous, f_onParams onParams);
        void startTempAccessPoint(const State::Instance * previous, f_onParams onParams);
        void startWpsConfig(const State::Instance * previous, f_onParams onParams);
        void stopTempMode(const State::Instance * previous, f_onParams onParams);
        void setNormalMode(const State::Instance * previous, f_onParams onParams);

      }
    }
  }
}
