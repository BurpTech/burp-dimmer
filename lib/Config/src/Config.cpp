#include "./Config.hpp"

namespace Config {

  const Redux::ReducerMap<ActionType, State> reducer;
  Redux::Store<ActionType> store;

}
