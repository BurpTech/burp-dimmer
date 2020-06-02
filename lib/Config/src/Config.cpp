#include "./Config.hpp"
#include "ArduinoJson.hpp"

namespace Config {

  const Redux::ReducerMap<State, ActionType, JsonObject> reducer;
  Redux::Store<State, ActionType, JsonObject> store;

}
