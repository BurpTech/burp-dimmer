#include "State.hpp"

namespace BurpDimmer {
  namespace Config {

    Memory memory;

    State::State(const Params * params) :
      light(params->light),
      network(params->network)
    {}

    void State::serialize(JsonObject & object) const {
      JsonObject lightObject = object[lightField].as<JsonObject>();
      light->serialize(lightObject);
      JsonObject networkObject = object[networkField].as<JsonObject>();
      network->serialize(networkObject);
    }

  }
}
