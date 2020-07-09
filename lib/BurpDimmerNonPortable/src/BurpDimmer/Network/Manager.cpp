#include "Manager.hpp"

namespace BurpDimmer {
  namespace Network {
    namespace Manager {

      Instance::Instance(const BurpLogger::Logger * logger) :
        _logger(logger),
        _config(nullptr)
      {}

      void Instance::setup(const Config * initial) {
        update(initial);
      }

      void Instance::update(const Config * next) {
        _config = next;
        _logger->info("_config->permMode: %u", _config->permMode);
        _logger->info("_config->tempMode: %u", _config->tempMode);
        _logger->info("_config->tempModeActive: %u", _config->tempModeActive);
        _logger->info("_config->accessPointTimeout: %lu", _config->accessPointTimeout);
      }

    }
  }
}
