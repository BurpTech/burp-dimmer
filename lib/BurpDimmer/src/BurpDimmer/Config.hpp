#pragma once

#include <CppRedux/Store.hpp>
#include <ArduinoJson.h>
#include "Config/ActionType.hpp"
#include "Config/State.hpp"

namespace BurpDimmer {
  namespace Config {

      using Store = CppRedux::Store<State, Action>;

      extern Store store;

      void init(const JsonObject & object);

  }
}
