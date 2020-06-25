#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {
        namespace State {

          constexpr PermMode defaultPermMode = PermMode::NORMAL;
          constexpr unsigned long defaultAccessPointTimeout = 0;

          Instance::Instance(const Params * params, unsigned long sequenceId) :
            permMode(params ? params->permMode : defaultPermMode),
            tempMode(params ? params->tempMode : defaultTempMode),
            tempModeActive(params ? params->tempModeActive : defaultTempModeActive),
            accessPointTimeout(params ? params->accessPointTimeout : defaultAccessPointTimeout),
            sequenceId(sequenceId)
          {}

          void Instance::serialize(JsonObject & object) const {
            // don't serialize the tempMode as it should not be restored
            object[modeField] = permModeNames[permMode];
            object[accessPointTimeoutField] = accessPointTimeout;
          }

          unsigned long Instance::getUid() const {
            return sequenceId;
          }

        }
      }
    }
  }
}
