#pragma once

#include <BurpRedux/Reducer.hpp>
#include "../ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      using Reducer = BurpRedux::Reducer::Instance<State::Instance, State::Params, ActionType::LIGHT_SET_STATE>;

    }
  }
}
