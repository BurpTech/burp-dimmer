#include "../Config.hpp"
#include "./Network.hpp"
#include "./Network/Manager.hpp"
#include "./Network/Station.hpp"
#include "./Network/AccessPoint.hpp"

namespace Config {
  namespace Network {

    const State * state() {
      return Config::state()->network;
    }

    void test() {
      Manager::test();
      Station::test();
      AccessPoint::test();
    }

  }
}
