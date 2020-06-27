#pragma once

#include <ArduinoJson.h>
#include <functional>
#include <BurpRedux/Action/Instance.hpp>
#include "../ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      using Action = BurpRedux::Action::Instance<State::Params, ActionType::LIGHT_SET_STATE>;
      void deserialize(const JsonObject & object, State::Params & params);

    }
  }
}
