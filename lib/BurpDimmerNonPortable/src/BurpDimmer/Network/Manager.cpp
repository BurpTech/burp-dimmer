#include "Manager.hpp"

namespace BurpDimmer {
  namespace Network {
    namespace Manager {

      Instance::Instance(const BurpLogger::Logger * logger) :
        _logger(logger),
        _config(nullptr)
      {}

      void Instance::setup(const Config * initial) {
        _config = initial;
      }

      void Instance::update(const Config * next) {
        _config = next;
        _logger->info("_config: %p", _config);
      }

    }
  }
}
