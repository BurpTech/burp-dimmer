#ifndef Config_hpp
#define Config_hpp

#include "./Redux/Store.hpp"
#include "./Redux/ReducerMap.hpp"

#include "./Config/ActionType.hpp"
#include "./Config/Network.hpp"

namespace Config {

    REDUX_REDUCERMAP_STATE_1(
      State, ActionType,
      Network::State, network, Network::reducer
    );
    const Redux::ReducerMap<ActionType, State> reducer;
    Redux::Store<ActionType> store;

}

#endif
