#pragma once

#include <ESP8266WiFi.h>

class FactorySettings {

  public:

    struct Values {
      char ssid[WL_SSID_MAX_LENGTH + 1];
      char password[WL_WPA_KEY_MAX_LENGTH + 1];
    };

    Values values = {"", ""};

    void setup();

  private:

    void _initialize();

};
