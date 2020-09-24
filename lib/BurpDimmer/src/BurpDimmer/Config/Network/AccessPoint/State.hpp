#pragma once

#include <BurpTree/State.hpp>
#include "../Constants.hpp"
#include "Types.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        class State : public BurpTree::State {

          public:

            char ssid[MAX_SSID_LENGTH + 1];
            const bool hasPassphrase;
            char passphrase[MAX_PASSPHRASE_LENGTH + 1];
            const uint8_t channel;
            const bool ssidHidden;
            const uint8_t maxConnections;
            const bool hasIpConfig;
            const IPConfig ipConfig;

            State(
              const char * ssid,
              const char * passphrase,
              const uint8_t channel,
              const bool ssidHidden,
              const uint8_t maxConnections,
              const IPConfig * ipConfig
            );
            bool serialize(const JsonVariant & serialized) const override;

        };

      }
    }
  }
}
