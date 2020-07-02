#include <BurpDebug.hpp>
#include "Manager.hpp"

namespace BurpDimmer {
  namespace Network {
    namespace Manager {

      Instance::Instance() :
        _config(nullptr)
      {}

      void Instance::setup(const Config * initial) {
        _config = initial;
      }

      void Instance::update(const Config * next) {
        _config = next;
        BURP_DEBUG_INFO("_config: %p", _config);
      }

    }
  }
}
