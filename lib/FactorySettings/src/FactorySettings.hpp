#pragma once

#include <ESP8266WiFi.h>
#include <cstdint>

class FactorySettings {

  public:

    struct Values {
      char ssid[WL_SSID_MAX_LENGTH + 1];
      char password[WL_WPA_KEY_MAX_LENGTH + 1];
    };

    Values values = {"", ""};

    void setup();

  private:

    // The version should change if format of serialized data changes
    static constexpr uint8_t _VERSION = 1;

    // Prefix for initialized names, etc
    static constexpr char _NAME_PREFIX[] = "burp-";

    // The length of the random name suffix
    static constexpr uint8_t _NAME_SUFFIX_LENGTH = 6;

    // The length of the random password
    static constexpr uint8_t _PASSWORD_LENGTH = 8;

    // This structure should never change
    struct Check {
      uint32_t version;
      uint32_t checksum;
    };

    static void _fillRandom(char * buffer, size_t offset, size_t length, size_t size);
    void _initialize();

};
