#include "Network.hpp"
#include "Network/AccessPoint.hpp"
#include "Network/Manager.hpp"
#include "Network/Station.hpp"

namespace Config {
  namespace Network {
    Module tests("Network", [](Describe & describe) {
      describe.include(AccessPoint::tests);
      describe.include(Manager::tests);
      describe.include(Station::tests);
    });
  }
}
