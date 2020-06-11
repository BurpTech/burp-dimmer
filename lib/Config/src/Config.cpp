#include "Config.hpp"

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

  void State::serialize(JsonObject & object) const {
    JsonObject networkObject = object[NETWORK_FIELD].as<JsonObject>();
    network->serialize(networkObject);
  }

  const Reducer reducer;
  Store store(reducer);

}
