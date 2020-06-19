#pragma once

#include <Redux/Store.hpp>
#include <ArduinoJson.h>
#include "Light/ActionType.hpp"

namespace BurpDimmer {
  namespace Light {

      using Store = Redux::Store<State, ActionType>;

      extern Store store;

      void init(const JsonObject & object);

  }
}
