#include <functional>
#include <BurpDimmer/Util/Debug.hpp>
#include "Manager.hpp"

namespace BurpDimmer {
  namespace Network {

    Manager::Manager() :
      _selector(_select)
    {}

    const Manager::State * Manager::_select(const Config::State * state) {
      return state->network->manager;
    }

    void Manager::notify() {
      _selector.check(Config::store.getState(), [&](const State * state) {
        BURP_DEBUG_INFO("BurpDimmer::Network::Manager::notify");
      });
    }

  }
}
