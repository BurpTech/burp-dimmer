#pragma once

#include <stddef.h>

namespace BurpDimmer {
  namespace Config {
    namespace Network {

        constexpr size_t MAX_SSID_LENGTH = 32;
        constexpr size_t MIN_PASSPHRASE_LENGTH = 8;
        constexpr size_t MAX_PASSPHRASE_LENGTH = 63;
        constexpr size_t MAX_HOSTNAME_LENGTH = 32;
        constexpr size_t BSSID_LENGTH = 6;

    }
  }
}
