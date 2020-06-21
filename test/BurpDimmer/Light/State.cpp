#include <unity.h>
#include <TestHelpers/withObj.hpp>
#include <TestHelpers/TestAsync.hpp>
#include <BurpDimmer/Light/State.hpp>
#include "State.hpp"

namespace BurpDimmerTest {
  namespace Light {
    namespace State {

      using namespace TestHelpers;
      using namespace BurpDimmer::Light::State;

      TestAsync testAsync;
      const class Instance * persistentState = nullptr;

      Module tests("State", [](Describe & describe) {

          describe.loop([]() {
              testAsync.loop();
          });

          describe.it("should use the correct field names for serialization", []() {
              TEST_ASSERT_EQUAL_STRING("on", onField);
              TEST_ASSERT_EQUAL_STRING("level", levelField);
              TEST_ASSERT_EQUAL_STRING("pwm", pwmField);
          });

          describe.describe("serialize", [](Describe & describe) {
              describe.it("should populate the JSON object", []() {
                  const Fields fields = {
                    true,
                    5,
                    20,
                  };
                  const Params params = {
                    nullptr,
                    &fields
                  };
                  const class Instance state(&params);
                  withObj([&](JsonObject & obj) {
                      state.serialize(obj);
                      TEST_ASSERT_EQUAL(fields.on, obj[onField].as<bool>());
                      TEST_ASSERT_EQUAL(fields.level, obj[levelField].as<unsigned char>());
                      TEST_ASSERT_EQUAL(fields.pwm, obj[pwmField].as<unsigned char>());
                  });
              });
          });

          describe.async("memory", [](Async & async, f_done & done) {
              const Fields fields = {
                false,
                15,
                78
              };
              const Params params = {
                nullptr,
                &fields
              };
              persistentState = memory.create(&params);
              testAsync.callbackOnce([&]() {
                  async.it("should persist the state", [&]() {
                      TEST_ASSERT_EQUAL(false, persistentState->on);
                      TEST_ASSERT_EQUAL(15, persistentState->level);
                      TEST_ASSERT_EQUAL(78, persistentState->pwm);
                  });
                  done();
              });
          });

      });

    }
  }
}
