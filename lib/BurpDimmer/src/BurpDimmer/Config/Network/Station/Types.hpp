#pragma once

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        struct IPConfig {
          uint32_t localIp;
          uint32_t gateway;
          uint32_t subnet;
          uint32_t dns1;
          uint32_t dns2;
        };

      }
    }
  }
}
