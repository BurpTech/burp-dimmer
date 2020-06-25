#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace State {

        Instance::Instance(const Params * params, unsigned long sequenceId) :
          accessPoint(params->accessPoint),
          manager(params->manager),
          station(params->station),
          sequenceId(sequenceId)
        {}

        void Instance::serialize(JsonObject & object) const {
          JsonObject accessPointObject = object[accessPointField].as<JsonObject>();
          accessPoint->serialize(accessPointObject);
          JsonObject managerObject = object[managerField].as<JsonObject>();
          manager->serialize(managerObject);
          JsonObject stationObject = object[stationField].as<JsonObject>();
          station->serialize(stationObject);
        }

        unsigned long Instance::getUid() const {
          return sequenceId;
        }

      }
    }
  }
}
