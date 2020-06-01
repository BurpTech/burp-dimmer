#pragma once

#include "./Manager/Reducer.hpp"
#include "./Manager/Actions.hpp"

namespace Config {
  namespace Network {
    namespace Manager {
      namespace Actions {
        extern const NextMode nextMode;
        extern const SetPermMode setPermModeNormal;
        extern const SetPermMode setPermModeAccessPoint;
        extern const SetPermMode setPermModeOff;
        extern const SetTempMode setTempModeAccessPoint;
        extern const SetTempMode setTempModeWpsConfig;
      }
      extern Reducer reducer;
    }
  }
}
