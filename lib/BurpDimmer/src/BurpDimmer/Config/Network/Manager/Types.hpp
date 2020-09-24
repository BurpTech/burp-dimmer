#pragma once

#include <stddef.h>
#include <stdint.h>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        enum PermMode : size_t {
          NORMAL = 0,
          ACCESS_POINT,
          OFF,
          count
        };

        enum class TempMode {
          ACCESS_POINT,
          WPS_CONFIG
        };

        using Timeout = uint32_t;

      }
    }
  }
}
