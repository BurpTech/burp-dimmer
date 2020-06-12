#include "Network.hpp"

namespace Config {
  namespace Network {

    constexpr char MANAGER_FIELD[] = "manager";
    constexpr char STATION_FIELD[] = "station";
    constexpr char ACCESS_POINT_FIELD[] = "accessPoint";

    State::State(const State * previous, const JsonObject & object) :
      manager(Manager::reducer.init(
        previous ? previous->manager : nullptr,
        object[MANAGER_FIELD].as<JsonObject>()
      )),
      station(Station::reducer.init(
        previous ? previous->station : nullptr,
        object[STATION_FIELD].as<JsonObject>()
      )),
      accessPoint(AccessPoint::reducer.init(
        previous ? previous->accessPoint : nullptr,
        object[ACCESS_POINT_FIELD].as<JsonObject>()
      )) {
    }

    State::State(const State * previous, const Redux::Action<ActionType> & action) :
      manager(Manager::reducer.reduce(previous->manager, action)),
      station(Station::reducer.reduce(previous->station, action)),
      accessPoint(AccessPoint::reducer.reduce(previous->accessPoint, action)) {
    }

    void State::serialize(JsonObject & object) const {
      JsonObject managerObject = object[MANAGER_FIELD].as<JsonObject>();
      manager->serialize(managerObject);
      JsonObject stationObject = object[STATION_FIELD].as<JsonObject>();
      station->serialize(stationObject);
      JsonObject accessPointObject = object[ACCESS_POINT_FIELD].as<JsonObject>();
      accessPoint->serialize(accessPointObject);
    }

    const Reducer reducer;

  }
}
