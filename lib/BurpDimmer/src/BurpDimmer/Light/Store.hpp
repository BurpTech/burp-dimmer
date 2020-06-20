#pragma once

#include <CppRedux/Store.hpp>
#include <ArduinoJson.h>
#include "State.hpp"
#include "ActionType.hpp"

namespace BurpDimmer {
  namespace Light {

      using Store = CppRedux::Store<State, Action>;

  }
}
