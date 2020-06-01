#include "./Actions.hpp"

namespace Config {
  namespace Network {
    namespace Manager {
      namespace Actions {

        Deserialize::Deserialize(const JsonObject & object) : 
          Redux::Action<ActionType>(ActionType::NETWORK_MANAGER_DESERIALIZE),
          object(object) {
        }

        SetAccessPointTimeout::SetAccessPointTimeout(const unsigned long timeout) : 
          Redux::Action<ActionType>(ActionType::NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT),
          timeout(timeout) {
        }

        NextMode::NextMode() : 
          Redux::Action<ActionType>(ActionType::NETWORK_MANAGER_NEXT_PERM_MODE) {
        }

        SetPermMode::SetPermMode(PermMode mode) : 
          Redux::Action<ActionType>(ActionType::NETWORK_MANAGER_SET_PERM_MODE),
          mode(mode) {
        }

        SetTempMode::SetTempMode(TempMode mode) : 
          Redux::Action<ActionType>(ActionType::NETWORK_MANAGER_SET_TEMP_MODE),
          mode(mode) {
        }

      }
    }
  }
}
