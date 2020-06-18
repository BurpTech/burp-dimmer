#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      Memory::Pair<State, Params> memory;

      State::State(const Params * params) :
        accessPoint(params->accessPoint),
        manager(params->manager),
        station(params->station)
      {}

      void State::serialize(JsonObject & object) const {
        JsonObject accessPointObject = object[accessPointField].as<JsonObject>();
        accessPoint->serialize(accessPointObject);
        JsonObject managerObject = object[managerField].as<JsonObject>();
        manager->serialize(managerObject);
        JsonObject stationObject = object[stationField].as<JsonObject>();
        station->serialize(stationObject);
      }

    }
  }
}
