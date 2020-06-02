#include "../Config.hpp"
#include "./Network.hpp"
#include "./Network/Manager.hpp"
#include "./Network/Station.hpp"

namespace Config {
  namespace Network {

    const State * state() {
      return Config::state()->network;
    }

    void deserialize() {
      Manager::deserialize();
      Station::deserialize();
    }

    void test() {
      Manager::test();
      Station::test();
    }

  }
}
