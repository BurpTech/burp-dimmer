#pragma once

#include <Redux/Action.hpp>

namespace Config {

  enum class ActionType {
    NETWORK_MANAGER_SET_STATE,
    NETWORK_STATION_SET_STATE,
    NETWORK_ACCESS_POINT_SET_STATE,
    LIGHT_SET_STATE
  };

  using Action = Redux::Action<ActionType>;

}
