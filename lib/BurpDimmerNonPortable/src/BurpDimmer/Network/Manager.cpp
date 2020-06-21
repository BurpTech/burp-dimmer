#include <BurpDimmer/Util/Debug.hpp>
#include "Manager.hpp"

namespace BurpDimmer {
  namespace Network {
    namespace Manager {

      Instance::Instance(const State * state) :
        _state(state)
      {}

      void Instance::onPublish(const State * state) {
        _state = state;
        BURP_DEBUG_INFO("state: %p", state);
      }

      Instance * instance;

      void init(const State * state) {
        instance = new Instance(state);
      }

      void deinit() {
        delete instance;
      }

    }
  }
}
