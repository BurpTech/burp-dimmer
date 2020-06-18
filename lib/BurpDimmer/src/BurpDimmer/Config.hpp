#pragma once

#include <Redux/Store.hpp>
#include <ArduinoJson.h>
#include "Config/ActionType.hpp"

namespace BurpDimmer {
  namespace Config {

      using Store = Redux::Store<State, ActionType>;

      extern Store store;

      void init(const JsonObject & object);

  }
}
