#include "Serialization.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        State::State(
            const PermMode permMode,
            const TempMode tempMode,
            const bool tempModeActive,
            const Timeout accessPointTimeout
        ) :
          permMode(permMode),
          tempMode(tempMode),
          tempModeActive(tempModeActive),
          accessPointTimeout(accessPointTimeout)
        {}

        bool State::serialize(const JsonVariant & serialized) const {
          Serialization serialization;
          // don't serialize the tempMode as it should not be restored
          serialization.root.mode.value = permMode;
          serialization.root.accessPointTimeout.value = accessPointTimeout;
          return serialization.serialize(serialized);
        }

      }
    }
  }
}
