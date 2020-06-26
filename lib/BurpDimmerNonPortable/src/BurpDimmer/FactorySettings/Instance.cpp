#include "Instance.hpp"

#include <stdint.h>
#include <EEPROM.h>
#include <CRC32.h>

#include <BurpDebug.hpp>

namespace BurpDimmer {
  namespace FactorySettings {

    // The version should change if format of serialized data changes
    constexpr uint8_t version = 1;

    // Prefix for initialized names, etc
    constexpr char namePrefix[] = "burp-";

    // The length of the random name suffix
    constexpr uint8_t nameSuffixLength = 6;

    // The length of the random password
    constexpr uint8_t passwordLength = 8;

    // This structure should never change
    struct Check {
      uint32_t version;
      uint32_t checksum;
    };

    // This uses the random function so
    // randomSeed should really be called before
    // calling this function
    void Instance::setup() {
      int address = 0;

      // Read the check
      Check check;
      BURP_DEBUG_INFO("Read check from EEPROM: address: [%d]", address);
      EEPROM.get(address, check);
      address += sizeof(Check);
      BURP_DEBUG_INFO("check values are: version: [%u]: checksum: [%08X]", check.version, check.checksum);

      if (check.version != version) {
        // This is the first version so just initialize
        // in the future if there is a new version then
        // we will need to check for a known old version
        // here and migrate initial values appropraitely
        BURP_DEBUG_INFO("Version unknown, initializing with new values: expected: [%u]: actual: [%u]", version, check.version);
        _initialize();
      } else {
        // We may have initialized already so read in
        // the initialized values
        BURP_DEBUG_INFO("Read initialized values from EEPROM: address: [%d]", address);
        EEPROM.get(address, _values);
        address += sizeof(Values);

        // We don't trust these values so let's calculate
        // the checksum and compare to the previously
        // read checksum
        uint32_t checksum = CRC32::calculate(
          (uint8_t *) &_values,
          sizeof(Values)
        );
        if (checksum != check.checksum) {
          BURP_DEBUG_INFO("Checksum invalid, initializing with new values: expected: [%08X]: actual: [%08X]", check.checksum, checksum);
          _initialize();
        } else {
          BURP_DEBUG_INFO("Checksum valid, initial values are: ssid: [%s]: password: [%s]", _values.ssid, _values.password);
        }
      }
    }

    void Instance::_initialize() {
      // initialize new random values
      strlcpy(_values.ssid, namePrefix, WL_SSID_MAX_LENGTH + 1);
      _fillRandom(_values.ssid, sizeof(namePrefix) - 1, nameSuffixLength, WL_SSID_MAX_LENGTH + 1);
      _fillRandom(_values.password, 0, passwordLength, WL_WPA_KEY_MAX_LENGTH + 1);

      // Create a new Check structure
      Check check;
      check.version = version;
      check.checksum = CRC32::calculate(
        (uint8_t *) &_values,
        sizeof(Values)
      );
      
      int address = 0;

      // write check to EEPROM
      BURP_DEBUG_INFO("check values are: version: [%u]: checksum: [%08X]", check.version, check.checksum);
      EEPROM.put(address, check);
      address += sizeof(Check);

      // write initial values to EEPROM
      BURP_DEBUG_INFO("initial values are: ssid: [%s]: password: [%s]", _values.ssid, _values.password);
      EEPROM.put(address, _values);
      address += sizeof(Values);

      //Commit the changes
      EEPROM.commit();
    }

    void Instance::_fillRandom(char * buffer, size_t offset, size_t length, size_t size) {
      BURP_DEBUG_INFO("parameters: buffer: [%s]: offset: [%d]: length: [%d]: size: [%d]", buffer, offset, length, size);
      int end = offset + length < size ? offset + length : size - 1;
      BURP_DEBUG_INFO("bounds checked: end: [%d]", end);
      int i = offset;
      for (; i < end; i++) {
        unsigned char r = random(0, 36);
        buffer[i] = (r >= 26 ? (r - 26) + '0' : r + 'a'); 
      }
      buffer[i] = 0;
      BURP_DEBUG_INFO("filled: buffer: [%s]", buffer);
    }

    Instance instance;

  }
}
