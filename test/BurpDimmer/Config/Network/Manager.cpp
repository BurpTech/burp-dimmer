#include <unity.h>
#include <BurpDimmer/Config.hpp>
#include <CppRedux/Selector.hpp>
#include <TestHelpers/TestSubscriber.hpp>
#include <TestHelpers/withObj.hpp>
#include "Manager.hpp"

namespace BurpDimmerTest {
  namespace Config {
    namespace Network {
      namespace Manager {

        using namespace TestHelpers;
        using namespace BurpDimmer::Config;
        using namespace BurpDimmer::Config::Network;
        using namespace BurpDimmer::Config::Network::Manager;

        using ConfigState = BurpDimmer::Config::State;
        using ManagerState = BurpDimmer::Config::Network::Manager::State;
        using Params = BurpDimmer::Config::Network::Manager::Params;
        using Selector = CppRedux::Selector<ConfigState, ManagerState>;

        TestSubscriber subscriber;

        Selector selector([](const ConfigState * state) {
            return state->network->manager;
        });

        Module tests("Manager", [](Describe & describe) {

          describe.setup([]() {
            store.setSubscriber(&subscriber);
          });

          describe.loop([]() {
            store.loop();
            subscriber.loop();
          });

          describe.beforeEach([]() {
            selector.reset();
          });

          describe.it("should have the correct field names for serialization", []() {
            TEST_ASSERT_EQUAL_STRING("mode", modeField);
            TEST_ASSERT_EQUAL_STRING("accessPointTimeout", accessPointTimeoutField);
          });

          describe.async("when initialised with an empty object", [](Async & async, f_done & done) {
            withObj([](JsonObject & obj) {
              init(obj);
            });
            selector.check(store.getState(), [&](const ManagerState * state) {
              async.it("should have the default state", [&]() {
                TEST_ASSERT_EQUAL_INT(PermMode::NORMAL, state->permMode);
                TEST_ASSERT_EQUAL_INT(TempMode::ACCESS_POINT, state->tempMode);
                TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
                TEST_ASSERT_EQUAL_UINT32(0, state->accessPointTimeout);
              });
              done();
            });
          });

          describe.describe("when initialised with a serialized state", [](Describe & describe) {
            describe.beforeEach([]() {
              withObj([](JsonObject & obj) {
                obj[networkField][managerField][modeField] = "accessPoint";
                obj[networkField][managerField][accessPointTimeoutField] = 60000;
                init(obj);
              });
            });
            describe.async("then the selector", [](Async & async, f_done & done) {
              selector.check(store.getState(), [&](const ManagerState * state) {
                async.it("should provide the deserialized state", [&]() {
                  TEST_ASSERT_EQUAL_INT(PermMode::ACCESS_POINT, state->permMode);
                  TEST_ASSERT_EQUAL_INT(TempMode::ACCESS_POINT, state->tempMode);
                  TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
                  TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
                });
                done();
              });
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
              describe.async("then the selector", [](Async & async, f_done & done) {
                selector.check(store.getState(), [&](const ManagerState * state) {
                  async.it("should provide the state", [&]() {
                    TEST_ASSERT_EQUAL_INT(PermMode::OFF, state->permMode);
                    TEST_ASSERT_EQUAL_INT(TempMode::WPS_CONFIG, state->tempMode);
                    TEST_ASSERT_EQUAL_INT(true, state->tempModeActive);
                    TEST_ASSERT_EQUAL_UINT32(30000, state->accessPointTimeout);
                  });
                  done();
                });
              });
            });

          });

        });

      }
    }
  }
}
