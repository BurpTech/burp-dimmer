#pragma once

#include <CppRedux/Store.hpp>
#include "State.hpp"
#include "ActionType.hpp"

namespace BurpDimmer {
  namespace Config {

      using Store = CppRedux::Store<State, Action>;

  }
}
