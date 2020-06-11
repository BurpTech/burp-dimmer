#include "Config.hpp"
#include "Config/Network.hpp"

#include <unity.h>
#include <Config.hpp>

namespace Config {
  Module tests("Config", [](Describe & describe) {

    describe.it("should have the correct field names for serialization", []() {
      TEST_ASSERT_EQUAL_STRING("network", State::NETWORK_FIELD);
    });

    describe.include(Network::tests);

  });
}
