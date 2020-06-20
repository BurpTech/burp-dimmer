#include <functional>
#include <BurpDimmer/Util/Debug.hpp>
#include "Manager.hpp"

namespace BurpDimmer {
  namespace Network {

    Manager manager(Config::networkManagerSelector);

    using namespace Config::Network::Manager;

    Manager::Manager(const Manager::Selector & selector) :
      _selector(selector)
    {}

    void Manager::notify() {
      const State * state = _selector.getState();
      BURP_DEBUG_INFO("state: %p", state);
    }

  }
}
