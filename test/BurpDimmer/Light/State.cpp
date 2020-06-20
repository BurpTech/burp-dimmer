#include <unity.h>
#include <TestHelpers/withObj.hpp>
#include <BurpDimmer/Light/State.hpp>
#include "State.hpp"

namespace BurpDimmerTest {
  namespace Light {
    namespace State {

      using namespace TestHelpers;
      using namespace BurpDimmer::Light;

      Module tests("State", [](Describe & describe) {

          describe.it("should use the correct field names for serialization", []() {
              TEST_ASSERT_EQUAL_STRING("on", onField);
              TEST_ASSERT_EQUAL_STRING("level", levelField);
              TEST_ASSERT_EQUAL_STRING("pwm", pwmField);
          });

          describe.describe("serialize", [](Describe & describe) {
              describe.it("should populate the JSON object", []() {
                  const Params params = {
                    true,
                    5,
                    20,
                  };
                  const class State state(&params);
                  withObj([&](JsonObject & obj) {
                      state.serialize(obj);
                      TEST_ASSERT_EQUAL(params.on, obj[onField].as<bool>());
                      TEST_ASSERT_EQUAL(params.level, obj[levelField].as<unsigned char>());
                      TEST_ASSERT_EQUAL(params.pwm, obj[pwmField].as<unsigned char>());
                  });
              });
          });
      });

    }
  }
}
