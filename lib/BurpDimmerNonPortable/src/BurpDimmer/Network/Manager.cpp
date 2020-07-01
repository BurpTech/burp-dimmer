#include <BurpDebug.hpp>
#include "Manager.hpp"

namespace BurpDimmer {
  namespace Network {
    namespace Manager {

      Instance::Instance() :
        _config(nullptr)
      {}

      void Instance::setup(const BurpTree::State * state) {
        _config = state->as<Config>();
      }

      void Instance::onPublish(const BurpTree::State * state) {
        _config = state->as<Config>();
        BURP_DEBUG_INFO("_config: %p", _config);
      }

    }
  }
}
