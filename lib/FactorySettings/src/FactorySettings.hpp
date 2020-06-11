#pragma once

#include <ESP8266WiFi.h>
#include <stddef.h>

namespace FactorySettings {

  struct Values {
    char ssid[WL_SSID_MAX_LENGTH + 1];
    char password[WL_WPA_KEY_MAX_LENGTH + 1];
  };

  class Instance {

    public:

      Values values = {"", ""};

      void init();

    private:

      static void _fillRandom(char * buffer, size_t offset, size_t length, size_t size);
      void _initialize();


  };

  extern Instance instance;

}
