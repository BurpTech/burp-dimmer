#pragma once

#include <ESP8266WiFi.h>
#include <stddef.h>
#include <BurpLogger.hpp>
#include <BurpDimmer/FactorySettings/Interface.hpp>

namespace BurpDimmer {
  namespace FactorySettings {

    class Instance : public Interface {

      public:

        Instance(const BurpLogger::Logger * logger);
        void setup();
        const char * getHostname() const override;
        const char * getSsid() const override;
        const char * getPassphrase() const override;

      private:

        struct Values {
          char hostname[WL_SSID_MAX_LENGTH + 1];
          char ssid[WL_SSID_MAX_LENGTH + 1];
          char passphrase[WL_WPA_KEY_MAX_LENGTH + 1];
        };

        const BurpLogger::Logger * _logger;
        Values _values = {"", ""};
        static void _fillRandom(const BurpLogger::Logger * logger, char * buffer, size_t offset, size_t length, size_t size);
        void _initialize();


    };

  }
}
