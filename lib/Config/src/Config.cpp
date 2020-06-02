#include "./Config.hpp"

namespace Config {

  const Redux::ReducerMap<State, ActionType> reducer;
  Redux::Store<State, ActionType> store;

}
