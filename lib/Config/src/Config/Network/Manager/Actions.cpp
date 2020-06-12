#include "Actions.hpp"
#include "State.hpp"

namespace Config {
  namespace Network {
    namespace Manager {
      namespace Actions {

        namespace {
          const PermMode _permModeNormal = PermMode::NORMAL;
          const PermMode _permModeAccessPoint = PermMode::ACCESS_POINT;
          const PermMode _permModeOff = PermMode::OFF;
          const TempMode _tempModeAccessPoint = TempMode::ACCESS_POINT;
          const TempMode _tempModeWpsConfig = TempMode::WPS_CONFIG;
        }

        const Action nextPermMode(ActionType::NETWORK_MANAGER_NEXT_PERM_MODE);
        const Action setPermModeNormal(
          ActionType::NETWORK_MANAGER_SET_PERM_MODE,
          &_permModeNormal
        );
        const Action setPermModeAccessPoint(
          ActionType::NETWORK_MANAGER_SET_PERM_MODE,
          &_permModeAccessPoint
        );
        const Action setPermModeOff(
          ActionType::NETWORK_MANAGER_SET_PERM_MODE,
          &_permModeOff
        );
        const Action setTempModeAccessPoint(
          ActionType::NETWORK_MANAGER_SET_TEMP_MODE,
          &_tempModeAccessPoint
        );
        const Action setTempModeWpsConfig(
          ActionType::NETWORK_MANAGER_SET_TEMP_MODE,
          &_tempModeWpsConfig
        );

      }
    }
  }
}
