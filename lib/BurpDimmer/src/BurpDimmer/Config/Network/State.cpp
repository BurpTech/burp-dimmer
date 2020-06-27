#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace State {

        Instance::Instance() :
          BurpRedux::State::Instance(0),
          accessPoint(nullptr),
          manager(nullptr),
          station(nullptr)
        {}

        Instance::Instance(const Instance & instance, const unsigned long uid) :
          BurpRedux::State::Instance(uid),
          accessPoint(instance.accessPoint),
          manager(instance.manager),
          station(instance.station)
        {}

        void Instance::serialize(const JsonObject & object) const {
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
}
