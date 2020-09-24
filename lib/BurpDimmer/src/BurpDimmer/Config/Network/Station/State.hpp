#pragma once

#include <BurpTree/State.hpp>
#include "../Constants.hpp"
#include "Types.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        class State : public BurpTree::State {

          public:

            char hostname[MAX_HOSTNAME_LENGTH + 1];
            bool hasSsid;
            char ssid[MAX_SSID_LENGTH + 1];
            const bool hasPassphrase;
            char passphrase[MAX_PASSPHRASE_LENGTH + 1];
            const uint8_t channel;
            const bool hasBssid;
            uint8_t bssid[BSSID_LENGTH];
            const bool hasIpConfig;
            const IPConfig ipConfig;

            State(
              const char * hostname,
              const char * ssid,
              const char * passphrase,
              const uint8_t channel,
              const uint8_t * bssid,
              const IPConfig * ipConfig
            );
            bool serialize(const JsonVariant & serialized) const override;

        };

      }
    }
  }
}
