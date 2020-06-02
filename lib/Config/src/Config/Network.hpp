#pragma once

#include <Redux/ReducerMap.hpp>

#include "../ActionType.hpp"
#include "./Network/Manager.hpp"
#include "./Network/Station.hpp"
#include "./Network/AccessPoint.hpp"
#include "ArduinoJson.hpp"

namespace Config {
  namespace Network {

    class State {
      public:
        const Manager::State * manager;
        const Station::State * station;
        const AccessPoint::State * accessPoint;

        State(const State * previous, const JsonObject * object) :
          manager(Manager::reducer.init(
            previous ? previous->manager : nullptr,
            [&](Manager::Reducer::f_doInit doInit) {
              const JsonObject obj = (*object)["manager"];
              return doInit(&obj);
            }
          )),
          station(Station::reducer.init(
            previous ? previous->station : nullptr,
            [&](Station::Reducer::f_doInit doInit) {
              const JsonObject obj = (*object)["station"];
              return doInit(&obj);
            }
          )),
          accessPoint(AccessPoint::reducer.init(
            previous ? previous->accessPoint : nullptr,
            [&](AccessPoint::Reducer::f_doInit doInit) {
              const JsonObject obj = (*object)["accessPoint"];
              return doInit(&obj);
            }
          )) {
        }

        State(const State * previous, const Redux::Action<ActionType> & action) :
          manager(Manager::reducer.reduce(previous->manager, action)),
          station(Station::reducer.reduce(previous->station, action)),
          accessPoint(AccessPoint::reducer.reduce(previous->accessPoint, action)) {
        }
    };
    extern const Redux::ReducerMap<State, ActionType, JsonObject> reducer;

  }
}
