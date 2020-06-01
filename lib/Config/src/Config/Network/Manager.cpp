#include "./Manager.hpp"
#include "./Manager/State.hpp"

namespace Config {
  namespace Network {
    namespace Manager {
      namespace Actions {
        const NextMode nextMode;
        const SetPermMode setPermModeNormal(PermMode::NORMAL);
        const SetPermMode setPermModeAccessPoint(PermMode::ACCESS_POINT);
        const SetPermMode setPermModeOff(PermMode::OFF);
        const SetTempMode setTempModeAccessPoint(TempMode::ACCESS_POINT);
        const SetTempMode setTempModeWpsConfig(TempMode::WPS_CONFIG);
      }
      Reducer reducer;
    }
  }
}
