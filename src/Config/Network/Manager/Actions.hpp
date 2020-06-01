#pragma once

#include <ArduinoJson.h>
#include "../../../Util/Debug.hpp"
#include "../../../Redux/Action.hpp"
#include "../../ActionType.hpp"
#include "./State.hpp"

namespace Config {
  namespace Network {
    namespace Manager {
      namespace Actions {

        class Deserialize: public Redux::Action<ActionType> {
          public:
            const JsonObject & object;
            Deserialize(const JsonObject & object) : 
              Action(ActionType::NETWORK_MANAGER_DESERIALIZE),
              object(object) {
            }
        };

        class SetAccessPointTimeout: public Redux::Action<ActionType> {
          public:
            const unsigned long timeout;
            SetAccessPointTimeout(const unsigned long timeout) : 
              Action(ActionType::NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT),
              timeout(timeout) {
            }
        };

        class NextMode: public Redux::Action<ActionType> {
          public:
            NextMode() : 
              Action(ActionType::NETWORK_MANAGER_NEXT_PERM_MODE) {
            }
        };

        class SetPermMode: public Redux::Action<ActionType> {
          public:
            PermMode mode;
            SetPermMode(PermMode mode) : 
              Action(ActionType::NETWORK_MANAGER_SET_PERM_MODE),
              mode(mode) {
            }
        };

        class SetTempMode: public Redux::Action<ActionType> {
          public:
            TempMode mode;
            SetTempMode(TempMode mode) : 
              Action(ActionType::NETWORK_MANAGER_SET_TEMP_MODE),
              mode(mode) {
            }
        };

      }
    }
  }
}
