#pragma once

#include <CppRedux/Action.hpp>

namespace BurpDimmer {
  namespace Light {

    enum class ActionType {
      SET_STATE
    };

    using Action = CppRedux::Action<ActionType>;

  }
}
