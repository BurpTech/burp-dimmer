#pragma once

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        struct IPConfig {
          uint32_t localIp;
          uint32_t gateway;
          uint32_t subnet;
        };

      }
    }
  }
}