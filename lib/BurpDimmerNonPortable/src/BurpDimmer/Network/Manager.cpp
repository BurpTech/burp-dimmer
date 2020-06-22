#include <BurpDebug.hpp>
#include "Manager.hpp"

namespace BurpDimmer {
  namespace Network {
    namespace Manager {

      Instance::Instance() :
        _state(nullptr)
      {}

      void Instance::setup(const State * state) {
        _state = state;
      }

      void Instance::onPublish(const State * state) {
        _state = state;
        BURP_DEBUG_INFO("state: %p", state);
      }

      Instance instance;

      void setup(const State * state) {
        instance.setup(state);
      }

    }
  }
}
