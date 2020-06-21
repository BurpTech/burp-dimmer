#include <unity.h>
#include <BurpDimmer/Config/State.hpp>
#include "Config/Network.hpp"
#include "Config.hpp"

namespace BurpDimmerTest {
  namespace Config {
    Module tests("Config", [](Describe & describe) {

      using namespace BurpDimmer::Config::State;

      describe.it("should have the correct field names for serialization", []() {
        TEST_ASSERT_EQUAL_STRING("network", networkField);
        TEST_ASSERT_EQUAL_STRING("light", lightField);
      });

      describe.include(Network::tests);

    });
  }
}
