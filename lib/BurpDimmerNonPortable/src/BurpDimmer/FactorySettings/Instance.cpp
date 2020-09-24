#include <stdint.h>
#include <EEPROM.h>
#include <CRC32.h>
#include "Instance.hpp"

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

    Instance::Instance(const BurpLogger::Logger * logger) :
      _logger(logger)
    {}

    // This uses the random function so
    // randomSeed should really be called before
    // calling this function
    void Instance::setup() {
      int address = 0;

      // Read the check
      Check check;
      _logger->info("Read check from EEPROM: address: [%d]", address);
      EEPROM.get(address, check);
      address += sizeof(Check);
      _logger->info("check values are: version: [%u]: checksum: [%08X]", check.version, check.checksum);

      if (check.version != version) {
        // This is the first version so just initialize
        // in the future if there is a new version then
        // we will need to check for a known old version
        // here and migrate initial values appropraitely
        _logger->info("Version unknown, initializing with new values: expected: [%u]: actual: [%u]", version, check.version);
        _initialize();
      } else {
        // We may have initialized already so read in
        // the initialized values
        _logger->info("Read initialized values from EEPROM: address: [%d]", address);
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
          _logger->info("Checksum invalid, initializing with new values: expected: [%08X]: actual: [%08X]", check.checksum, checksum);
          _initialize();
        } else {
          _logger->info("Checksum valid, initial values are: hostname: [%s]: ssid: [%s]: password: [%s]", _values.hostname, _values.ssid, _values.passphrase);
        }
      }
    }

    const char * Instance::getHostname() const {
      return _values.hostname;
    }

    const char * Instance::getSsid() const {
      return _values.ssid;
    }

    const char * Instance::getPassphrase() const {
      return _values.passphrase;
    }

    void Instance::_initialize() {
      // initialize a random hostname
      strlcpy(_values.hostname, namePrefix, WL_SSID_MAX_LENGTH + 1);
      _fillRandom(_logger, _values.hostname, sizeof(namePrefix) - 1, nameSuffixLength, WL_SSID_MAX_LENGTH + 1);
      // use the same value for the ssid
      strlcpy(_values.ssid, _values.hostname, WL_SSID_MAX_LENGTH + 1);
      // initialize a random passphrase
      _fillRandom(_logger, _values.passphrase, 0, passwordLength, WL_WPA_KEY_MAX_LENGTH + 1);

      // Create a new Check structure
      Check check;
      check.version = version;
      check.checksum = CRC32::calculate(
        (uint8_t *) &_values,
        sizeof(Values)
      );
      
      int address = 0;

      // write check to EEPROM
      _logger->info("check values are: version: [%u]: checksum: [%08X]", check.version, check.checksum);
      EEPROM.put(address, check);
      address += sizeof(Check);

      // write initial values to EEPROM
      _logger->info("initial values are: hostname: [%s]: ssid: [%s]: password: [%s]", _values.hostname, _values.ssid, _values.passphrase);
      EEPROM.put(address, _values);
      address += sizeof(Values);

      //Commit the changes
      EEPROM.commit();
    }

    void Instance::_fillRandom(const BurpLogger::Logger * logger, char * buffer, size_t offset, size_t length, size_t size) {
      logger->debug("_fillRandom: parameters: buffer: [%s]: offset: [%d]: length: [%d]: size: [%d]", buffer, offset, length, size);
      int end = offset + length < size ? offset + length : size - 1;
      logger->debug("_fillRandom: bounds checked: end: [%d]", end);
      int i = offset;
      for (; i < end; i++) {
        unsigned char r = random(0, 36);
        buffer[i] = (r >= 26 ? (r - 26) + '0' : r + 'a'); 
      }
      buffer[i] = 0;
      logger->debug("_fillRandom: filled: buffer: [%s]", buffer);
    }

  }
}
