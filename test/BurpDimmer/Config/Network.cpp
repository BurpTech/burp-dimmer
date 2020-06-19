#include <unity.h>
#include <BurpDimmer/Config/Network/State.hpp>
#include "Network/AccessPoint.hpp"
#include "Network/Manager.hpp"
#include "Network/Station.hpp"
#include "Network.hpp"

namespace BurpDimmerTest {
  namespace Config {
    namespace Network {
      Module tests("Network", [](Describe & describe) {

        using namespace BurpDimmer::Config::Network;

        describe.it("should have the correct field names for serialization", []() {
          TEST_ASSERT_EQUAL_STRING("manager", managerField);
          TEST_ASSERT_EQUAL_STRING("station", stationField);
          TEST_ASSERT_EQUAL_STRING("accessPoint", accessPointField);
        });

        describe.include(AccessPoint::tests);
        describe.include(Manager::tests);
        describe.include(Station::tests);

      });
    }
  }
}
