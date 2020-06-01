#pragma once

#include "./Manager/Reducer.hpp"
#include "Manager/Actions.hpp"
#include "Manager/State.hpp"

namespace Config {
  namespace Network {
    namespace Manager {

      Actions::NextMode nextMode;
      Actions::SetPermMode setPermModeNormal(State::PermMode::NORMAL);
      Actions::SetPermMode setPermModeAccessPoint(State::PermMode::ACCESS_POINT);
      Actions::SetPermMode setPermModeOff(State::PermMode::OFF);
      Actions::SetTempMode setTempModeAccessPoint(State::TempMode::ACCESS_POINT);
      Actions::SetTempMode setTempModeWpsConfig(State::TempMode::WPS_CONFIG);

      Reducer reducer;

    }
  }
}
