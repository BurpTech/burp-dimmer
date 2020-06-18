#include "Reducer.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        const Reducer reducer;

        const State * Reducer::reduce(const State * previous, const Action & action) const {
          switch (action.type) {
            case ActionType::NETWORK_MANAGER_NEXT_PERM_MODE: {
              const Params params = {
                static_cast<PermMode>((previous->permMode + 1) % PermMode::count),
                previous->tempMode,
                false,
                previous->accessPointTimeout
              };
              return memory.create(&params);
            }
            case ActionType::NETWORK_MANAGER_START_TEMP_ACCESS_POINT: {
              const Params params = {
                previous->permMode,
                TempMode::ACCESS_POINT,
                true,
                previous->accessPointTimeout
              };
              return memory.create(&params);
            }
            case ActionType::NETWORK_MANAGER_START_WPS_CONFIG: {
              const Params params = {
                previous->permMode,
                TempMode::WPS_CONFIG,
                true,
                previous->accessPointTimeout
              };
              return memory.create(&params);
            }
            case ActionType::NETWORK_MANAGER_STOP_TEMP_MODE: {
              const Params params = {
                previous->permMode,
                previous->tempMode,
                false,
                previous->accessPointTimeout
              };
              return memory.create(&params);
            }
            case ActionType::NETWORK_MANAGER_SET_NORMAL_MODE: {
              const Params params = {
                PermMode::NORMAL,
                previous->tempMode,
                false,
                previous->accessPointTimeout
              };
              return memory.create(&params);
            }
            case ActionType::NETWORK_MANAGER_SET_CONFIG: {
              return memory.create(action.payload<Params>());
            }
            default:
              return previous;
          }
        }

      }
    }
  }
}
