#pragma once

namespace BurpDimmer {
  namespace Config {

    enum ActionType : unsigned int {
      NETWORK_MANAGER_SET_STATE,
      NETWORK_STATION_SET_STATE,
      NETWORK_ACCESS_POINT_SET_STATE,
      LIGHT_SET_STATE
    };

  }
}
