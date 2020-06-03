#include "./Actions.hpp"
#include "ActionType.hpp"
#include "Config/Network/Manager/State.hpp"

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

        const Redux::Action<ActionType> nextPermMode
          (ActionType::NETWORK_MANAGER_NEXT_PERM_MODE);
        const Redux::Action<ActionType> setPermModeNormal
          (ActionType::NETWORK_MANAGER_SET_PERM_MODE,
           &_permModeNormal);
        const Redux::Action<ActionType> setPermModeAccessPoint
          (ActionType::NETWORK_MANAGER_SET_PERM_MODE,
           &_permModeAccessPoint);
        const Redux::Action<ActionType> setPermModeOff
          (ActionType::NETWORK_MANAGER_SET_PERM_MODE,
           &_permModeOff);
        const Redux::Action<ActionType> setTempModeAccessPoint
          (ActionType::NETWORK_MANAGER_SET_TEMP_MODE,
           &_tempModeAccessPoint);
        const Redux::Action<ActionType> setTempModeWpsConfig
          (ActionType::NETWORK_MANAGER_SET_TEMP_MODE,
           &_tempModeWpsConfig);

      }
    }
  }
}
