#pragma once

#include <Redux/Store.hpp>
#include <Redux/ReducerMap.hpp>
#include "./ActionType.hpp"
#include "./Config/Network.hpp"

namespace Config {

    REDUX_REDUCERMAP_STATE_1(
      State, ActionType,
      Network::State, network, Network::reducer
    );
    extern const Redux::ReducerMap<ActionType, State> reducer;
    extern Redux::Store<ActionType> store;

}
