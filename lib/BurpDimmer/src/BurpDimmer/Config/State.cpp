#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace State {

      Instance::Instance() :
        BurpRedux::State::Instance(0),
        light(nullptr),
        network(nullptr)
      {}

      Instance::Instance(const Instance & instance, const unsigned long uid) :
        BurpRedux::State::Instance(uid),
        light(instance.light),
        network(instance.network)
      {}

      void Instance::serialize(const JsonObject & object) const {
        JsonObject lightObject = object[lightField].as<JsonObject>();
        light->serialize(lightObject);
        JsonObject networkObject = object[networkField].as<JsonObject>();
        network->serialize(networkObject);
      }

    }
  }
}
