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

        using Action = BurpRedux::Action::Instance<State::Params, ActionType::NETWORK_MANAGER_SET_STATE>;
        void deserialize(const JsonObject & object, State::Params & params);
        void nextPermMode(const State::Instance * previous, State::Params & params);
        void startTempAccessPoint(const State::Instance * previous, State::Params & params);
        void startWpsConfig(const State::Instance * previous, State::Params & params);
        void stopTempMode(const State::Instance * previous, State::Params & params);
        void setNormalMode(const State::Instance * previous, State::Params & params);

      }
    }
  }
}
