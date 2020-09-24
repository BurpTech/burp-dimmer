#pragma once

#include <BurpTree/State.hpp>
#include "Types.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        class State : public BurpTree::State {

          public:

            const PermMode permMode;
            const TempMode tempMode;
            const bool tempModeActive;
            const Timeout accessPointTimeout;

            State(
                const PermMode permMode,
                const TempMode tempMode,
                const bool tempModeActive,
                const Timeout accessPointTimeout
            );
            bool serialize(const JsonVariant & serialized) const override;

        };

      }
    }
  }
}
