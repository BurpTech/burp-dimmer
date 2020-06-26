#include "Light/Deserialize.hpp"
#include "Network/Deserialize.hpp"
#include "Deserialize.hpp"

namespace BurpDimmer {
  namespace Config {

    void deserialize(State::Creator & creator, const JsonObject & object, f_onState onState) {
      JsonObject lightObject = object[State::lightField].as<JsonObject>();
      JsonObject networkObject = object[State::networkField].as<JsonObject>();
      Light::deserialize(lightObject, [&](const Light::State::Instance * lightState) {
          Network::deserialize(networkObject, [&](const Network::State::Instance * networkState) {
              onState(creator.init({
                lightState,
                networkState
              }));
          });
      });
    }

  }
}
