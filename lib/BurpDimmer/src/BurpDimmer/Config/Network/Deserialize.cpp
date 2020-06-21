#include "AccessPoint/Deserialize.hpp"
#include "Manager/Deserialize.hpp"
#include "Station/Deserialize.hpp"
#include "Deserialize.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      void deserialize(const JsonObject & object, f_onState onState) {
        JsonObject accessPointObject = object[State::accessPointField].as<JsonObject>();
        JsonObject managerObject = object[State::managerField].as<JsonObject>();
        JsonObject stationObject = object[State::stationField].as<JsonObject>();
        AccessPoint::deserialize(accessPointObject, [&](const AccessPoint::State::Instance * accessPointState) {
            Manager::deserialize(managerObject, [&](const Manager::State::Instance * managerState) {
                Station::deserialize(stationObject, [&](const Station::State::Instance * stationState) {
                    const State::Params params = {
                      accessPointState,
                      managerState,
                      stationState
                    };
                    onState(State::memory.create(&params));
                });
            });
        });
      }

    }
  }
}
