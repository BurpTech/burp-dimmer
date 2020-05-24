#ifndef FactorySettings_hpp
#define FactorySettings_hpp

#include <EEPROM.h>
#include <CRC32.h>

#include "Debug.hpp"

#include "Wifi/Config.hpp"

// The version should change if format of serialized data changes
#define FACTORY_SETTINGS_VERSION 1

// Prefix for initialized names, etc
#define FACTORY_SETTINGS_NAME_PREFIX "burp-"

// The length of the random name suffix
#define FACTORY_SETTINGS_NAME_SUFFIX_LENGTH 6

// The length of the random password
#define FACTORY_SETTINGS_PASSWORD_LENGTH 8

class FactorySettings {
  // This structure should never change
  struct Check {
    uint32_t version;
    uint32_t checksum;
  };

  static void _fillRandom(char * buffer, size_t offset, size_t length, size_t size) {
    DEBUG_PRINT("parameters: buffer: [%s]: offset: [%d]: length: [%d]: size: [%d]", buffer, offset, length, size);
    int end = offset + length < size ? offset + length : size - 1;
    DEBUG_PRINT("bounds checked: end: [%d]", end);
    int i = offset;
    for (; i < end; i++) {
      byte r = random(0, 36);
      buffer[i] = (r >= 26 ? (r - 26) + '0' : r + 'a'); 
    }
    buffer[i] = 0;
    DEBUG_PRINT("filled: buffer: [%s]", buffer);
  }

  static void _initialize() {
    // initialize new random values
    strlcpy(values.ssid, FACTORY_SETTINGS_NAME_PREFIX, WIFI_CONFIG_SSID_BUFFER_SIZE);
    _fillRandom(values.ssid, sizeof(FACTORY_SETTINGS_NAME_PREFIX) - 1, FACTORY_SETTINGS_NAME_SUFFIX_LENGTH, WIFI_CONFIG_SSID_BUFFER_SIZE);
    _fillRandom(values.password, 0, FACTORY_SETTINGS_PASSWORD_LENGTH, WIFI_CONFIG_PASSWORD_BUFFER_SIZE);

    // Create a new Check structure
    Check check;
    check.version = FACTORY_SETTINGS_VERSION;
    check.checksum = CRC32::calculate(
      (uint8_t *) &values,
      sizeof(Values)
    );
    
    int address = 0;

    // write check to EEPROM
    DEBUG_PRINT("check values are: version: [%u]: checksum: [%08X]", check.version, check.checksum);
    EEPROM.put(address, check);
    address += sizeof(Check);

    // write initial values to EEPROM
    DEBUG_PRINT("initial values are: ssid: [%s]: password: [%s]", values.ssid, values.password);
    EEPROM.put(address, values);
    address += sizeof(Values);

    //Commit the changes
    EEPROM.commit();
  }

  public:
    struct Values {
      char ssid[WIFI_CONFIG_SSID_BUFFER_SIZE];
      char password[WIFI_CONFIG_PASSWORD_BUFFER_SIZE];
    };

    static Values values;

    // This uses the random function so
    // randomSeed should really be called before
    // calling this function
    static void initialize() {
      int address = 0;

      // Read the check
      Check check;
      DEBUG_PRINT("Read check from EEPROM: address: [%d]", address);
      EEPROM.get(address, check);
      address += sizeof(Check);
      DEBUG_PRINT("check values are: version: [%u]: checksum: [%08X]", check.version, check.checksum);

      if (check.version != FACTORY_SETTINGS_VERSION) {
        // This is the first version so just initialize
        // in the future if there is a new version then
        // we will need to check for a known old version
        // here and migrate initial values appropraitely
        DEBUG_PRINT("Version unknown, initializing with new values: expected: [%u]: actual: [%u]", FACTORY_SETTINGS_VERSION, check.version);
        _initialize();
      } else {
        // We may have initialized already so read in
        // the initialized values
        DEBUG_PRINT("Read initialized values from EEPROM: address: [%d]", address);
        EEPROM.get(address, values);
        address += sizeof(Values);

        // We don't trust these values so let's calculate
        // the checksum and compare to the previously
        // read checksum
        uint32_t checksum = CRC32::calculate(
          (uint8_t *) &values,
          sizeof(Values)
        );
        if (checksum != check.checksum) {
          DEBUG_PRINT("Checksum invalid, initializing with new values: expected: [%08X]: actual: [%08X]", check.checksum, checksum);
          _initialize();
        } else {
          DEBUG_PRINT("Checksum valid, initial values are: ssid: [%s]: password: [%s]", values.ssid, values.password);
        }
      }
    }
};

FactorySettings::Values FactorySettings::values;

#endif
