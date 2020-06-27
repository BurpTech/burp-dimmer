#pragma once

#include <ArduinoJson.h>
#include <functional>
#include <BurpRedux/Publisher/Interface.hpp>
#include <BurpRedux/Action/Instance.hpp>
#include "ActionType.hpp"
#include "State.hpp"
#include "Config.hpp"

namespace BurpDimmer {
  namespace Light {

    using Action = BurpRedux::Action::Instance<State::Params, ActionType::SET_STATE>;
    void deserialize(const JsonObject & object, State::Params & params);
    void applyConfig(const State::Instance * previous, const Config * config, State::Params & params);
    void toggle(const State::Instance * previous, State::Params & params);
    void increaseBrightness(const State::Instance * previous, State::Params & params);
    void decreaseBrightness(const State::Instance * previous, State::Params & params);

  }
}
