#include <unity.h>
#include <BurpDimmer/Config.hpp>
#include <TestHelpers/TestSubscriber.hpp>
#include <TestHelpers/withObj.hpp>
#include "Manager.hpp"

namespace BurpDimmerTest {
  namespace Config {
    namespace Network {
      namespace Manager {
        using namespace Actions;

        TestHelpers::TestSubscriber subscriber;

        Module tests("Manager", [](Describe & describe) {

          describe.setup([]() {
            store.setSubscriber(&subscriber);
          });

          describe.loop([]() {
            store.loop();
            subscriber.loop();
          });

          describe.it("should have the correct defaults", []() {
            TEST_ASSERT_EQUAL_INT(PermMode::NORMAL, State::DEFAULT_PERM_MODE);
            TEST_ASSERT_EQUAL_INT(TempMode::ACCESS_POINT, State::DEFAULT_TEMP_MODE);
            TEST_ASSERT_EQUAL_INT(false, State::DEFAULT_TEMP_MODE_ACTIVE);
            TEST_ASSERT_EQUAL_UINT32(0, State::DEFAULT_ACCESS_POINT_TIMEOUT);
          });

          describe.it("should have the correct field names for serialization", []() {
            TEST_ASSERT_EQUAL_STRING("mode", State::MODE_FIELD);
            TEST_ASSERT_EQUAL_STRING("accessPointTimeout", State::ACCESS_POINT_TIMEOUT_FIELD);
          });

          describe.describe("when initialised with an empty object", [](Describe & describe) {
            describe.beforeEach([]() {
              TestHelpers::withObj([](JsonObject & obj) {
                store.init(obj);
              });
            });

            describe.it("should have the default state", []() {
              auto state = store.getState()->network->manager;
              TEST_ASSERT_EQUAL_INT(State::DEFAULT_PERM_MODE, state->permMode);
              TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
              TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state->tempModeActive);
              TEST_ASSERT_EQUAL_UINT32(State::DEFAULT_ACCESS_POINT_TIMEOUT, state->accessPointTimeout);
            });

          });

          describe.describe("when initialised with a serialized state", [](Describe & describe) {
            describe.beforeEach([]() {
              TestHelpers::withObj([](JsonObject & obj) {
                obj[Config::State::NETWORK_FIELD][Network::State::MANAGER_FIELD][State::MODE_FIELD] = static_cast<int>(PermMode::ACCESS_POINT);
                obj[Config::State::NETWORK_FIELD][Network::State::MANAGER_FIELD][State::ACCESS_POINT_TIMEOUT_FIELD] = 60000;
                store.init(obj);
              });
            });

            describe.it("should have the deserialized state", []() {
              auto state = store.getState()->network->manager;
              TEST_ASSERT_EQUAL_INT(PermMode::ACCESS_POINT, state->permMode);
              TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
              TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state->tempModeActive);
              TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
            });

            describe.describe("then dispatch a deserialization action", [](Describe & describe) {
              describe.beforeEach([](f_done & done) {
                TestHelpers::withObj([](JsonObject & obj) {
                  obj[State::MODE_FIELD] = static_cast<int>(PermMode::OFF);
                  obj[State::ACCESS_POINT_TIMEOUT_FIELD] = 30000;
                  store.dispatch(Redux::Action<ActionType>(ActionType::NETWORK_MANAGER_DESERIALIZE, &obj));
                });
                subscriber.callbackOnce(done);
              });
              describe.it("should deserialize the state", []() {
                auto state = store.getState()->network->manager;
                TEST_ASSERT_EQUAL_INT(PermMode::OFF, state->permMode);
                TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
                TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state->tempModeActive);
                TEST_ASSERT_EQUAL_UINT32(30000, state->accessPointTimeout);
              });
            });

            describe.describe("then dispatch a set access point timeout action", [](Describe & describe) {
              describe.beforeEach([](f_done & done) {
                unsigned long timeout = 100000;
                store.dispatch(Redux::Action<ActionType>(ActionType::NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT, &timeout));
                subscriber.callbackOnce(done);
              });
              describe.it("should apply the setting", []() {
                auto state = store.getState()->network->manager;
                TEST_ASSERT_EQUAL_INT(PermMode::ACCESS_POINT, state->permMode);
                TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
                TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state->tempModeActive);
                TEST_ASSERT_EQUAL_UINT32(100000, state->accessPointTimeout);
              });
            });

            describe.async("then dispatch next mode actions", [](Async & async, f_done & done) {
              // set a temp mode to verify that setting a perm mode
              // turns it off
              store.dispatch(setTempModeWpsConfig);
              subscriber.callbackOnce([&]() {
                store.dispatch(nextPermMode);
                subscriber.callbackOnce([&]() {
                  async.it("should switch to the OFF mode", []() {
                    auto state = store.getState()->network->manager;
                    TEST_ASSERT_EQUAL_INT(PermMode::OFF, state->permMode);
                    TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
                    TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
                    TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
                  });
                  store.dispatch(nextPermMode);
                  subscriber.callbackOnce([&]() {
                    async.it("should switch to the NORMAL mode", []() {
                      auto state = store.getState()->network->manager;
                      TEST_ASSERT_EQUAL_INT(PermMode::NORMAL, state->permMode);
                      TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
                      TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
                      TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
                    });
                    store.dispatch(nextPermMode);
                    subscriber.callbackOnce([&]() {
                      async.it("should switch to the ACCESS_POINT mode", []() {
                        auto state = store.getState()->network->manager;
                        TEST_ASSERT_EQUAL_INT(PermMode::ACCESS_POINT, state->permMode);
                        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
                        TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
                        TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
                      });
                      store.dispatch(nextPermMode);
                      subscriber.callbackOnce([&]() {
                        async.it("should switch to the OFF mode", []() {
                          auto state = store.getState()->network->manager;
                          TEST_ASSERT_EQUAL_INT(PermMode::OFF, state->permMode);
                          TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
                          TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
                          TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
                        });
                        done();
                      });
                    });
                  });
                });
              });
            });

            describe.async("then dispatch set perm mode actions", [](Async & async, f_done & done) {
              // set a temp mode to verify that setting a perm mode
              // turns it off
              store.dispatch(setTempModeWpsConfig);
              subscriber.callbackOnce([&]() {
                store.dispatch(setPermModeOff);
                subscriber.callbackOnce([&]() {
                  async.it("should switch to the OFF mode", []() {
                    auto state = store.getState()->network->manager;
                    TEST_ASSERT_EQUAL_INT(PermMode::OFF, state->permMode);
                    TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
                    TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
                    TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
                  });
                  store.dispatch(setPermModeNormal);
                  subscriber.callbackOnce([&]() {
                    async.it("should switch to the NORMAL mode", []() {
                      auto state = store.getState()->network->manager;
                      TEST_ASSERT_EQUAL_INT(PermMode::NORMAL, state->permMode);
                      TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
                      TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
                      TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
                    });
                    store.dispatch(setPermModeAccessPoint);
                    subscriber.callbackOnce([&]() {
                      async.it("should switch to the ACCESS_POINT mode", []() {
                        auto state = store.getState()->network->manager;
                        TEST_ASSERT_EQUAL_INT(PermMode::ACCESS_POINT, state->permMode);
                        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state->tempMode);
                        TEST_ASSERT_EQUAL_INT(false, state->tempModeActive);
                        TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
                      });
                      done();
                    });
                  });
                });
              });
            });

            describe.async("then dispatch set temp mode actions", [](Async & async, f_done & done) {
              // set a perm mode to verify that setting a temp mode
              // turns it off
              store.dispatch(setPermModeOff);
              subscriber.callbackOnce([&]() {
                store.dispatch(setTempModeWpsConfig);
                subscriber.callbackOnce([&]() {
                  async.it("should switch to the WPS_CONFIG mode", []() {
                    auto state = store.getState()->network->manager;
                    TEST_ASSERT_EQUAL_INT(PermMode::OFF, state->permMode);
                    TEST_ASSERT_EQUAL_INT(TempMode::WPS_CONFIG, state->tempMode);
                    TEST_ASSERT_EQUAL_INT(true, state->tempModeActive);
                    TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
                  });
                  store.dispatch(setTempModeAccessPoint);
                  subscriber.callbackOnce([&]() {
                    async.it("should switch to the ACCESS_POINT mode", []() {
                      auto state = store.getState()->network->manager;
                      TEST_ASSERT_EQUAL_INT(PermMode::OFF, state->permMode);
                      TEST_ASSERT_EQUAL_INT(TempMode::ACCESS_POINT, state->tempMode);
                      TEST_ASSERT_EQUAL_INT(true, state->tempModeActive);
                      TEST_ASSERT_EQUAL_UINT32(60000, state->accessPointTimeout);
                    });
                    done();
                  });
                });
              });
            });

          });

        });

      }
    }
  }
}
