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

        describe.it("should have the correct field names for serialization", []() {
          TEST_ASSERT_EQUAL_STRING("manager", State::MANAGER_FIELD);
          TEST_ASSERT_EQUAL_STRING("station", State::STATION_FIELD);
          TEST_ASSERT_EQUAL_STRING("accessPoint", State::ACCESS_POINT_FIELD);
        });

        describe.include(AccessPoint::tests);
        describe.include(Manager::tests);
        describe.include(Station::tests);

      });
    }
  }
}
