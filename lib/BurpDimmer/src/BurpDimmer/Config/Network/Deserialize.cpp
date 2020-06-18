#include "AccessPoint/Deserialize.hpp"
#include "Manager/Deserialize.hpp"
#include "Station/Deserialize.hpp"
#include "Deserialize.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      void deserialize(const JsonObject & object, f_onState onState) {
        JsonObject accessPointObject = object[accessPointField].as<JsonObject>();
        JsonObject managerObject = object[managerField].as<JsonObject>();
        JsonObject stationObject = object[stationField].as<JsonObject>();
        AccessPoint::deserialize(accessPointObject, [&](const AccessPoint::State * accessPointState) {
            Manager::deserialize(managerObject, [&](const Manager::State * managerState) {
                Station::deserialize(stationObject, [&](const Station::State * stationState) {
                    const Params params = {
                      accessPointState,
                      managerState,
                      stationState
                    };
                    onState(memory.create(&params));
                });
            });
        });
      }

    }
  }
}
