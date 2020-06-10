#include "./Config.hpp"
#include "ArduinoJson.hpp"

namespace Config {

  constexpr char State::NETWORK_FIELD[];

  State::State(const State * previous, const JsonObject & object) :
    network(Network::reducer.init(
      previous ? previous->network : nullptr,
      object[NETWORK_FIELD].as<JsonObject>()
    )) {
  }

  State::State(const State * previous, const Redux::Action<ActionType> & action) :
    network(Network::reducer.reduce(previous->network, action)) {
  }

  const Redux::ReducerMap<State, ActionType, JsonObject> reducer;
  Redux::Store<State, ActionType, JsonObject> store(reducer);

}
