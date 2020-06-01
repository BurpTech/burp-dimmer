#pragma once

#include <Redux/ReducerMap.hpp>

#include "../ActionType.hpp"
#include "./Network/Manager.hpp"

namespace Config {
  namespace Network {

    REDUX_REDUCERMAP_STATE_1(
      State, ActionType,
      Manager::State, manager, Manager::reducer
    );
    extern const Redux::ReducerMap<ActionType, State> reducer;

  }
}
