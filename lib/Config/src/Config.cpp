#include "Config.hpp"

namespace Config {

  constexpr char NETWORK_FIELD[] = "network";
  constexpr char LIGHT_FIELD[] = "light";

  State::State(const State * previous, const JsonObject & object) :
    network(Network::reducer.init(
      previous ? previous->network : nullptr,
      object[NETWORK_FIELD].as<JsonObject>()
    )),
    light(Light::reducer.init(
      previous ? previous->light : nullptr,
      object[LIGHT_FIELD].as<JsonObject>()
    ))
  {}

  State::State(const State * previous, const Redux::Action<ActionType> & action) :
    network(Network::reducer.reduce(previous->network, action)),
    light(Light::reducer.reduce(previous->light, action))
  {}

  void State::serialize(JsonObject & object) const {
    JsonObject networkObject = object[NETWORK_FIELD].as<JsonObject>();
    network->serialize(networkObject);
    JsonObject lightObject = object[LIGHT_FIELD].as<JsonObject>();
    network->serialize(lightObject);
  }

  const Reducer reducer;
  Store store(reducer);

}
