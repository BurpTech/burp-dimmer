#pragma once

#include "./Manager/Reducer.hpp"
#include "Manager/Actions.hpp"
#include "Manager/State.hpp"

namespace Config {
  namespace Network {
    namespace Manager {
      namespace Actions {
        NextMode nextMode;
        SetPermMode setPermModeNormal(PermMode::NORMAL);
        SetPermMode setPermModeAccessPoint(PermMode::ACCESS_POINT);
        SetPermMode setPermModeOff(PermMode::OFF);
        SetTempMode setTempModeAccessPoint(TempMode::ACCESS_POINT);
        SetTempMode setTempModeWpsConfig(TempMode::WPS_CONFIG);
      }
      Reducer reducer;

    }
  }
}
