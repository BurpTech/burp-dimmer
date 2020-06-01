#pragma once

#include "../Redux/ReducerMap.hpp"

#include "./Network/Manager.hpp"
#include "./Config/ActionType.hpp"

namespace Config {
  namespace Network {

    REDUX_REDUCERMAP_STATE_1(
      State, ActionType,
      Manager::State, manager, Manager::reducer
    );
    const Redux::ReducerMap<ActionType, State> reducer;

  }
}
