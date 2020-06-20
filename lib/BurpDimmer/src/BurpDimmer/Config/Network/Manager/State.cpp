#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        Memory memory;

        constexpr PermMode defaultPermMode = PermMode::NORMAL;
        constexpr unsigned long defaultAccessPointTimeout = 0;

        State::State(const Params * params) :
          permMode(params ? params->permMode : defaultPermMode),
          tempMode(params ? params->tempMode : defaultTempMode),
          tempModeActive(params ? params->tempModeActive : defaultTempModeActive),
          accessPointTimeout(params ? params->accessPointTimeout : defaultAccessPointTimeout)
        {}

        void State::serialize(JsonObject & object) const {
          // don't serialize the tempMode as it should not be restored
          object[modeField] = permModeNames[permMode];
          object[accessPointTimeoutField] = accessPointTimeout;
        }

      }
    }
  }
}
