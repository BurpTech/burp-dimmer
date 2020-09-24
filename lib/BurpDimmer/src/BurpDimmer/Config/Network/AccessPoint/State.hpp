#pragma once

#include <BurpTree/State.hpp>
#include "Types.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        class State : public BurpTree::State {

          public:

            char ssid[WL_SSID_MAX_LENGTH + 1];
            const bool hasPassphrase;
            char passphrase[WL_WPA_KEY_MAX_LENGTH + 1];
            const int8_t channel;
            const bool ssidHidden;
            const int8_t maxConnections;
            const bool hasIpConfig;
            const IPConfig ipConfig;

            State(
              const char * ssid,
              const char * passphrase,
              const int8_t channel,
              const bool ssidHidden,
              const int8_t maxConnections,
              const IPConfig * ipConfig
            );
            bool serialize(const JsonVariant & serialized) const override;

        };

      }
    }
  }
}
