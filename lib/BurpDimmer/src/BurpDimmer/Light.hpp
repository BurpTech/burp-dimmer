#pragma once

#include <Redux/Store.hpp>
#include <ArduinoJson.h>
#include "Light/Reducer.hpp"

namespace BurpDimmer {
  namespace Light {

      using Store = Redux::Store<State, ActionType, JsonObject>;

      extern const Reducer reducer;
      extern Store store;

  }
}
