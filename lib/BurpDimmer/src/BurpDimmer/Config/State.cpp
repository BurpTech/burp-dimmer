#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace State {

      Instance::Instance(const Params * params, unsigned long sequenceId) :
        light(params->light),
        network(params->network),
        sequenceId(sequenceId)
      {}

      void Instance::serialize(JsonObject & object) const {
        JsonObject lightObject = object[lightField].as<JsonObject>();
        light->serialize(lightObject);
        JsonObject networkObject = object[networkField].as<JsonObject>();
        network->serialize(networkObject);
      }

      unsigned long Instance::getUid() const {
        return sequenceId;
      }

    }
  }
}
