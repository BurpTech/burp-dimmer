#ifndef FirstBoot_hpp
#define FirstBoot_hpp

#include <EEPROM.h>
#include <CRC32.h>

#include "Debug.hpp"

#include "WifiConfig.hpp"

// The version should change if format of serialized data changes
#define FIRST_BOOT_VERSION 1

// Prefix for initialized names, etc
#define FIRST_BOOT_NAME_PREFIX "burp-"

// The length of the random name suffix
#define FIRST_BOOT_NAME_SUFFIX_LENGTH 6

// The length of the random password
#define FIRST_BOOT_PASSWORD_LENGTH 8

class FirstBoot {
  // This structure should never change
  struct Check {
    uint32_t version;
    uint32_t checksum;
  };

  static void _fillRandom(char * buffer, size_t offset, size_t length, size_t size) {
    DEBUG_LIST_START(F("parameters"));
    DEBUG_LIST_VAL(F("buffer"), buffer);
    DEBUG_LIST_VAL(F("offset"), offset);
    DEBUG_LIST_VAL(F("length"), length);
    DEBUG_LIST_VAL(F("size"), size);
    DEBUG_LIST_END;
    int end = offset + length < size ? offset + length : size - 1;
    DEBUG_VAL(F("bounds checked"), F("end"), end);
    int i = offset;
    for (; i < end; i++) {
      byte r = random(0, 36);
      buffer[i] = (r >= 26 ? (r - 26) + '0' : r + 'a'); 
    }
    buffer[i] = 0;
    DEBUG_VAL(F("filled"), F("buffer"), buffer);
  }

  static void _initialize() {
    // initialize new random values
    strlcpy(initialValues.ssid, FIRST_BOOT_NAME_PREFIX, WIFI_CONFIG_SSID_BUFFER_SIZE);
    _fillRandom(initialValues.ssid, sizeof(FIRST_BOOT_NAME_PREFIX) - 1, FIRST_BOOT_NAME_SUFFIX_LENGTH, WIFI_CONFIG_SSID_BUFFER_SIZE);
    _fillRandom(initialValues.password, 0, FIRST_BOOT_PASSWORD_LENGTH, WIFI_CONFIG_PASSWORD_BUFFER_SIZE);

    // Create a new Check structure
    Check check;
    check.version = FIRST_BOOT_VERSION;
    check.checksum = CRC32::calculate(
      (uint8_t *) &initialValues,
      sizeof(InitialValues)
    );
    
    int address = 0;

    // write check to EEPROM
    DEBUG_LIST_START(F("check values are"));
    DEBUG_LIST_VAL(F("version"), check.version);
    DEBUG_LIST_VAL(F("checksum"), check.checksum);
    DEBUG_LIST_END
    EEPROM.put(address, check);
    address += sizeof(Check);

    // write initial values to EEPROM
    DEBUG_LIST_START(F("initial values are"));
    DEBUG_LIST_VAL(F("ssid"), initialValues.ssid);
    DEBUG_LIST_VAL(F("password"), initialValues.password);
    DEBUG_LIST_END;
    EEPROM.put(address, initialValues);
    address += sizeof(InitialValues);

    //Commit the changes
    EEPROM.commit();
  }

  public:
    struct InitialValues {
      char ssid[WIFI_CONFIG_SSID_BUFFER_SIZE];
      char password[WIFI_CONFIG_PASSWORD_BUFFER_SIZE];
    };

    static InitialValues initialValues;

    // This uses the random function so
    // randomSeed should really be called before
    // calling this function
    static void initialize() {
      int address = 0;

      // Read the check
      Check check;
      DEBUG_VAL(F("Read check from EEPROM"), F("address"), address);
      EEPROM.get(address, check);
      address += sizeof(Check);
      DEBUG_LIST_START(F("check values are"));
      DEBUG_LIST_VAL(F("version"), check.version);
      DEBUG_LIST_VAL(F("checksum"), check.checksum);
      DEBUG_LIST_END

      if (check.version != FIRST_BOOT_VERSION) {
        // This is the first version so just initialize
        // in the future if there is a new version then
        // we will need to check for a known old version
        // here and migrate initial values appropraitely
        DEBUG_LIST_START(F("Version unknown, initializing with new values"));
        DEBUG_LIST_VAL(F("expected"), check.version);
        DEBUG_LIST_VAL(F("actual"), FIRST_BOOT_VERSION);
        DEBUG_LIST_END;
        _initialize();
      } else {
        // We may have initialized already so read in
        // the initialized values
        DEBUG_VAL(F("Read initialized values from EEPROM"), F("EEPROM address"), address);
        EEPROM.get(address, initialValues);
        address += sizeof(InitialValues);

        // We don't trust these values so let's calculate
        // the checksum and compare to the previously
        // read checksum
        uint32_t checksum = CRC32::calculate(
          (uint8_t *) &initialValues,
          sizeof(InitialValues)
        );
        if (checksum != check.checksum) {
          DEBUG_LIST_START(F("Checksum invalid, initializing with new values"));
          DEBUG_LIST_VAL(F("expected"), check.checksum);
          DEBUG_LIST_VAL(F("actual"), checksum);
          DEBUG_LIST_END;
          _initialize();
        } else {
          DEBUG_LIST_START(F("Checksum valid, initial values are"));
          DEBUG_LIST_VAL(F("ssid"), initialValues.ssid);
          DEBUG_LIST_VAL(F("password"), initialValues.password);
          DEBUG_LIST_END;
        }
      }
    }
};

FirstBoot::InitialValues FirstBoot::initialValues;

#endif
