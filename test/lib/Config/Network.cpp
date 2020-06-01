#include "../Config.hpp"
#include "./Network.hpp"
#include "./Network/Manager.hpp"

namespace Config {
  namespace Network {

    const State * state() {
      return Config::state()->network;
    }

    void deserialize() {
      Manager::deserialize();
    }

    void test() {
      Manager::test();
    }

  }
}
