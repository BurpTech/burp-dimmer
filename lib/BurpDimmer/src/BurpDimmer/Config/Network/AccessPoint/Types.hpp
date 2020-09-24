#pragma once

#include <ESP8266WiFi.h>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        struct IPConfig {
          IPAddress localIp;
          IPAddress gateway;
          IPAddress subnet;
        };

      }
    }
  }
}
