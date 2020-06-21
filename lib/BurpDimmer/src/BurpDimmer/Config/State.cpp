#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace State {

      Memory memory;

      Instance::Instance(const Params * params) :
        light(params->light),
        network(params->network)
      {}

      void Instance::serialize(JsonObject & object) const {
        JsonObject lightObject = object[lightField].as<JsonObject>();
        light->serialize(lightObject);
        JsonObject networkObject = object[networkField].as<JsonObject>();
        network->serialize(networkObject);
      }

    }
  }
}
