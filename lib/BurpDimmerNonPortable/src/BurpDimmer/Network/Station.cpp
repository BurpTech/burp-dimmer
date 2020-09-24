#include "Station.hpp"

namespace BurpDimmer {
  namespace Network {
    namespace Station {

      Instance::Instance(const BurpLogger::Logger * logger) :
        _logger(logger),
        _config(nullptr)
      {}

      void Instance::setup(const Config * initial) {
        update(initial);
      }

      void Instance::update(const Config * next) {
        _config = next;
        _logger->info("_config->hostname: %s", _config->hostname);
        if (_config->hasSsid) {
          _logger->info("_config->ssid: %s", _config->ssid);
        } else {
          _logger->info("_config->ssid: NULL");
        }
        if (_config->hasPassphrase) {
          _logger->info("_config->passphrase: %s", _config->passphrase);
        } else {
          _logger->info("_config->passphrase: NULL");
        }
        _logger->info("_config->channel: %u", _config->channel);
        if (_config->hasBssid) {
          _logger->info(
            "_config->bssid: %02X:%02X:%02X:%02X:%02X:%02X",
            _config->bssid[0],
            _config->bssid[1],
            _config->bssid[2],
            _config->bssid[3],
            _config->bssid[4],
            _config->bssid[5]
          );
        } else {
          _logger->info("_config->bssid: NULL");
        }
        if (_config->hasIpConfig) {
          _logger->info("_config->ipConfig.localIp: 0x%08X", _config->ipConfig.localIp);
          _logger->info("_config->ipConfig.gateway: 0x%08X", _config->ipConfig.gateway);
          _logger->info("_config->ipConfig.subnet: 0x%08X", _config->ipConfig.subnet);
          _logger->info("_config->ipConfig.dns1: 0x%08X", _config->ipConfig.dns1);
          _logger->info("_config->ipConfig.dns2: 0x%08X", _config->ipConfig.dns2);
        } else {
          _logger->info("_config->ipConfig: NULL");
        }
      }

    }
  }
}
