#pragma once

#include <Redux/ReducerMap.hpp>

#include "../ActionType.hpp"
#include "./Network/Manager.hpp"
#include "./Network/Station.hpp"
#include "./Network/AccessPoint.hpp"

namespace Config {
  namespace Network {

    REDUX_REDUCERMAP_STATE_3(
      State, ActionType,
      Manager::State, manager, Manager::reducer,
      Station::State, station, Station::reducer,
      AccessPoint::State, accessPoint, AccessPoint::reducer
    );
    extern const Redux::ReducerMap<ActionType, State> reducer;

  }
}
