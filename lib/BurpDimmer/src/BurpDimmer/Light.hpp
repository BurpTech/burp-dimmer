#pragma once

#include <CppRedux/Store.hpp>
#include <ArduinoJson.h>
#include "Light/ActionType.hpp"
#include "Light/State.hpp"

namespace BurpDimmer {
  namespace Light {

      using Store = CppRedux::Store<State, Action>;

      extern Store store;

      void init(const JsonObject & object);

  }
}
