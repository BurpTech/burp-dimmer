#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace State {

      Instance::Instance(const Params * params, const unsigned long uid) :
        BurpRedux::State::Instance(uid),
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
