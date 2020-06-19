#pragma once

#include <Redux/Action.hpp>

namespace BurpDimmer {
  namespace Light {

    enum class ActionType {
      SET_STATE
    };

    using Action = Redux::Action<ActionType>;

  }
}
