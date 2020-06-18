#pragma once

#include <Redux/Action.hpp>
#include <functional>

namespace Config {

  enum class ActionType {
    NETWORK_MANAGER_NEXT_PERM_MODE,
    NETWORK_MANAGER_START_TEMP_ACCESS_POINT,
    NETWORK_MANAGER_START_WPS_CONFIG,
    NETWORK_MANAGER_SET_CONFIG,
    NETWORK_STATION_SET_CONFIG,
    NETWORK_ACCESS_POINT_SET_CONFIG,
    LIGHT_SET_CONFIG
  };

  using Action = Redux::Action<ActionType>;

}
