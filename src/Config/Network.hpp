#ifndef Config_Network_hpp
#define Config_Network_hpp

#include "../Redux/ReducerMap.hpp"
#include "./ActionType.hpp"

#include "./Network/Manager.hpp"

namespace Config {
  namespace Network {

    const ManagerReducer managerReducer;
    REDUX_REDUCERMAP_STATE_1(
      State, ActionType,
      Manager, manager, managerReducer
    );
    const Redux::ReducerMap<ActionType, State> reducer;

  }
}

#endif
