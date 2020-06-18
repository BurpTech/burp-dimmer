#include "Light/Deserialize.hpp"
#include "Network/Deserialize.hpp"
#include "Deserialize.hpp"

namespace Config {

  void deserialize(const JsonObject & object, f_onState onState) {
    JsonObject lightObject = object[lightField].as<JsonObject>();
    JsonObject networkObject = object[networkField].as<JsonObject>();
    Light::deserialize(lightObject, [&](const Light::State * lightState) {
        Network::deserialize(networkObject, [&](const Network::State * networkState) {
            const Params params = {
              lightState,
              networkState
            };
            onState(memory.create(&params));
        });
    });
  }

}
