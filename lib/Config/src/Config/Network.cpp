#include "./Network.hpp"

namespace Config {
  namespace Network {

    State::State(const State * previous, const JsonObject & object) :
      manager(Manager::reducer.init(
        previous ? previous->manager : nullptr,
        object["manager"].as<JsonObject>()
      )),
      station(Station::reducer.init(
        previous ? previous->station : nullptr,
        object["station"].as<JsonObject>()
      )),
      accessPoint(AccessPoint::reducer.init(
        previous ? previous->accessPoint : nullptr,
        object["accessPoint"].as<JsonObject>()
      )) {
    }

    State::State(const State * previous, const Redux::Action<ActionType> & action) :
      manager(Manager::reducer.reduce(previous->manager, action)),
      station(Station::reducer.reduce(previous->station, action)),
      accessPoint(AccessPoint::reducer.reduce(previous->accessPoint, action)) {
    }

    const Redux::ReducerMap<State, ActionType, JsonObject> reducer;

  }
}
