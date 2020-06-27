#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {
        namespace State {

          constexpr PermMode defaultPermMode = PermMode::NORMAL;
          constexpr unsigned long defaultAccessPointTimeout = 0;

          Instance::Instance(const Params & params, const unsigned long uid) :
            BurpRedux::State::Instance(uid),
            permMode(params.error == Error::noError ? params.permMode : defaultPermMode),
            tempMode(params.error == Error::noError ? params.tempMode : defaultTempMode),
            tempModeActive(params.error == Error::noError ? params.tempModeActive : defaultTempModeActive),
            accessPointTimeout(params.error == Error::noError ? params.accessPointTimeout : defaultAccessPointTimeout)
          {}

          void Instance::serialize(const JsonObject & object) const {
            // don't serialize the tempMode as it should not be restored
            object[modeField] = permModeNames[permMode];
            object[accessPointTimeoutField] = accessPointTimeout;
          }

        }
      }
    }
  }
}
