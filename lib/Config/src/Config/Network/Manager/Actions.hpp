#pragma once

#include <ArduinoJson.h>
#include <Redux/Action.hpp>
#include "../../../ActionType.hpp"
#include "./State.hpp"

namespace Config {
  namespace Network {
    namespace Manager {
      namespace Actions {

        extern const Redux::Action<ActionType> nextPermMode;
        extern const Redux::Action<ActionType> setPermModeNormal;
        extern const Redux::Action<ActionType> setPermModeAccessPoint;
        extern const Redux::Action<ActionType> setPermModeOff;
        extern const Redux::Action<ActionType> setTempModeAccessPoint;
        extern const Redux::Action<ActionType> setTempModeWpsConfig;

      }
    }
  }
}
