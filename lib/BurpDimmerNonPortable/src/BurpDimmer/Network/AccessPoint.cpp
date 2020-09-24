#include "AccessPoint.hpp"

namespace BurpDimmer {
  namespace Network {
    namespace AccessPoint {

      Instance::Instance(const BurpLogger::Logger * logger) :
        _logger(logger),
        _config(nullptr)
      {}

      void Instance::setup(const Config * initial) {
        update(initial);
      }

      void Instance::update(const Config * next) {
        _config = next;
        _logger->info("_config->ssid: %s", _config->ssid);
        if (_config->hasPassphrase) {
          _logger->info("_config->passphrase: %s", _config->passphrase);
        } else {
          _logger->info("_config->passphrase: NULL");
        }
        _logger->info("_config->ssidHidden: %u", _config->ssidHidden);
        _logger->info("_config->channel: %u", _config->channel);
        _logger->info("_config->maxConnections: %u", _config->maxConnections);
        if (_config->hasIpConfig) {
          _logger->info("_config->ipConfig.localIp: 0x%08X", _config->ipConfig.localIp);
          _logger->info("_config->ipConfig.gateway: 0x%08X", _config->ipConfig.gateway);
          _logger->info("_config->ipConfig.subnet: 0x%08X", _config->ipConfig.subnet);
        } else {
          _logger->info("_config->ipConfig: NULL");
        }
      }

    }
  }
}
