#pragma once

#include <BurpRedux/Reducer/Instance.hpp>
#include <BurpRedux/Action/Instance.hpp>
#include "State.hpp"
#include "ActionType.hpp"

namespace BurpDimmer {
  namespace Light {

    using Reducer = BurpRedux::Reducer::Instance<State::Instance, State::Params, ActionType::SET_STATE>;

  }
}
