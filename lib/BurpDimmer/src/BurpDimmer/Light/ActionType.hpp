#pragma once

#include <BurpRedux/Action.hpp>

namespace BurpDimmer {
  namespace Light {

    enum class ActionType {
      SET_STATE
    };

    using Action = BurpRedux::Action<ActionType>;

  }
}
