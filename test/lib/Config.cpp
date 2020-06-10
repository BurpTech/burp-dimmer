#include "Config.hpp"
#include "Config/Network.hpp"

namespace Config {
  Module tests("Config", [](Describe & describe) {
    describe.include(Network::tests);
  });
}
