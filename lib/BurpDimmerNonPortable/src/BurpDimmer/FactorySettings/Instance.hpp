#pragma once

#include <ESP8266WiFi.h>
#include <stddef.h>
#include "Interface.hpp"

namespace BurpDimmer {
  namespace FactorySettings {

    class Instance : public Interface {

      public:

        void setup();
        const char * getSsid() const override;
        const char * getPassword() const override;

      private:

        struct Values {
          char ssid[WL_SSID_MAX_LENGTH + 1];
          char password[WL_WPA_KEY_MAX_LENGTH + 1];
        };

        Values _values = {"", ""};
        static void _fillRandom(char * buffer, size_t offset, size_t length, size_t size);
        void _initialize();


    };

    extern Instance instance;

  }
}
