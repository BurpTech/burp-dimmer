#include <unity.h>
#include <BurpDimmer/Config.hpp>
#include <BurpDimmer/Config/Store.hpp>
#include <BurpDimmer/Config/State.hpp>
#include <BurpDimmer/Config/Network/State.hpp>
#include <BurpDimmer/Config/Network/Manager/Selector.hpp>
#include <BurpDimmer/Config/Network/Manager/State.hpp>
#include <TestHelpers/TestSubscriber.hpp>
#include <TestHelpers/withObj.hpp>
#include "Manager.hpp"

namespace BurpDimmerTest {
  namespace Config {
    namespace Network {
      namespace Manager {

        using namespace TestHelpers;
        using namespace BurpDimmer::Config;
        using namespace BurpDimmer::Config::State;
        using namespace BurpDimmer::Config::Network::State;
        using namespace BurpDimmer::Config::Network::Manager;
        using namespace BurpDimmer::Config::Network::Manager::State;

        using Instance = BurpDimmer::Config::Network::Manager::State::Instance;
        using Params = BurpDimmer::Config::Network::Manager::State::Params;

        TestSubscriber<Instance> subscriber;

        Module tests("Manager", [](Describe & describe) {

          describe.it("should have the correct field names for serialization", []() {
            TEST_ASSERT_EQUAL_STRING("mode", modeField);
            TEST_ASSERT_EQUAL_STRING("accessPointTimeout", accessPointTimeoutField);
          });

          describe.describe("when initialised with an empty object", [](Describe & describe) {
            describe.setup([]() {
                withObj([](JsonObject & obj) {
                    read(obj);
                });
            });

            describe.loop([]() {
                store.loop();
            });

            describe.it("should have the default state", []() {
              const Instance * state = selector.getState();
              TEST_ASSERT_EQUAL_INT(PermMode::NORMAL, state->permMode);
              TEST_ASSERT_EQUAL_INT(TempMode::ACCESS_POINT, state->tempMode);
              TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
              TEST_ASSERT_EQUAL_UINT32(0, state->accessPointTimeout);
            });
          });

          describe.describe("when initialised with a serialized state", [](Describe & describe) {
            describe.setup([]() {
                withObj([](JsonObject & obj) {
                    obj[networkField][managerField][modeField] = "accessPoint";
                    obj[networkField][managerField][accessPointTimeoutField] = 60000;
                    read(obj);
                });
            });

            describe.loop([]() {
                store.loop();
            });

            describe.it("should have the deserialized state", []() {
              const Instance * state = selector.getState();
              TEST_ASSERT_EQUAL_INT(PermMode::ACCESS_POINT, state->permMode);
              TEST_ASSERT_EQUAL_INT(TempMode::ACCESS_POINT, state->tempMode);
              TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
              TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
            });

            describe.describe("then dispatch a set state action", [](Describe & describe) {
              describe.beforeEach([](f_done & done) {
                Params params = {
                  PermMode::OFF,
                  TempMode::WPS_CONFIG,
                  true,
                  30000
                };
                store.dispatch(Action(ActionType::NETWORK_MANAGER_SET_STATE, &params));
                subscriber.callbackOnce(done);
              });
              describe.it("should have the new state", [&]() {
                const Instance * state = selector.getState();
                TEST_ASSERT_EQUAL_INT(PermMode::OFF, state->permMode);
                TEST_ASSERT_EQUAL_INT(TempMode::WPS_CONFIG, state->tempMode);
                TEST_ASSERT_EQUAL_INT(true, state->tempModeActive);
                TEST_ASSERT_EQUAL_UINT32(30000, state->accessPointTimeout);
              });
            });

          });

        });

      }
    }
  }
}
