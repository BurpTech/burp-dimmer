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
        State(const State * previous, const JsonObject & object);
        State(const State * previous, const Redux::Action<ActionType> & action);
    };
    extern const Redux::ReducerMap<State, ActionType, JsonObject> reducer;

  }
}
