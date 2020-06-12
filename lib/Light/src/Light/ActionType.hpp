#pragma once

#include <Redux/Action.hpp>

namespace Light {

  enum class ActionType {
    DESERIALIZE,
    TOGGLE,
    TURN_ON,
    TURN_OFF,
    SET_BRIGHTNESS,
    INCREASE_BRIGHTNESS,
    DECREASE_BRIGHTNESS,
    APPLY_CONFIG
  };

  using Action = Redux::Action<ActionType>;

}
