#ifndef NATIVE
#include <Arduino.h>
#endif

#include <unity.h>
#include <functional>
#include <ArduinoJson.h>

#include "../../src/Redux/Subscriber.hpp"
#include "../../src/Config.hpp"

using f_onObj = std::function<void(JsonObject & obj)>;
void withObj(f_onObj onObj) {
  StaticJsonDocument<1024> doc;
  JsonObject obj = doc.to<JsonObject>();
  onObj(obj);
}

namespace Config {
  void initialize();

  class Subscriber : public Redux::Subscriber {
    public:
      const State * state = nullptr;
      void notify() override {
        state = store.getState<State>();
      }
  };
  Subscriber subscriber;

  namespace Network {
    namespace Manager {
      const State * state() {
        return subscriber.state->network->manager;
      }

      void testDefaults() {
        TEST_ASSERT_EQUAL_INT(State::PermMode::NORMAL, State::DEFAULT_PERM_MODE);
        TEST_ASSERT_EQUAL_INT(State::TempMode::ACCESS_POINT, State::DEFAULT_TEMP_MODE);
        TEST_ASSERT_EQUAL_INT(false, State::DEFAULT_TEMP_MODE_ACTIVE);
        TEST_ASSERT_EQUAL_UINT32(0, State::DEFAULT_ACCESS_POINT_TIMEOUT);
      }

      void testFieldNames() {
        TEST_ASSERT_EQUAL_STRING("mode", State::MODE_FIELD);
        TEST_ASSERT_EQUAL_STRING("accessPointTimeout", State::ACCESS_POINT_TIMEOUT_FIELD);
      }

      void testInitialState() {
        initialize();
        TEST_ASSERT_EQUAL_INT(State::PermMode::ACCESS_POINT, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
      }

      void testDeserializeAction() {
        initialize();
        withObj([&](JsonObject & object) {
          object[State::MODE_FIELD] = static_cast<int>(State::PermMode::OFF);
          object[State::ACCESS_POINT_TIMEOUT_FIELD] = 30000;
          const Actions::Deserialize action(object);
          store.dispatch(action);
          TEST_ASSERT_EQUAL_INT(State::PermMode::OFF, state()->permMode);
          TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
          TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state()->tempModeActive);
          TEST_ASSERT_EQUAL_UINT32(30000, state()->accessPointTimeout);
        });
      }

      void testSetAccessPointTimeoutAction() {
        initialize();
        const Actions::SetAccessPointTimeout action(100000);
        store.dispatch(action);
        TEST_ASSERT_EQUAL_INT(State::PermMode::ACCESS_POINT, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE_ACTIVE, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(100000, state()->accessPointTimeout);
      }

      void testNextModeAction() {
        initialize();

        // set a temp mode to verify that setting a perm mode
        // turns it off
        store.dispatch(setTempModeWpsConfig);

        store.dispatch(nextMode);
        TEST_ASSERT_EQUAL_INT(State::PermMode::OFF, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(nextMode);
        TEST_ASSERT_EQUAL_INT(State::PermMode::NORMAL, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(nextMode);
        TEST_ASSERT_EQUAL_INT(State::PermMode::ACCESS_POINT, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(nextMode);
        TEST_ASSERT_EQUAL_INT(State::PermMode::OFF, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
      }

      void testSetPermMode() {
        initialize();

        // set a temp mode to verify that setting a perm mode
        // turns it off
        store.dispatch(setTempModeWpsConfig);

        store.dispatch(setPermModeOff);
        TEST_ASSERT_EQUAL_INT(State::PermMode::OFF, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(setPermModeNormal);
        TEST_ASSERT_EQUAL_INT(State::PermMode::NORMAL, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(setPermModeAccessPoint);
        TEST_ASSERT_EQUAL_INT(State::PermMode::ACCESS_POINT, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::DEFAULT_TEMP_MODE, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(false, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
      }

      void testSetTempMode() {
        initialize();

        // set a perm mode to verify that setting a temp mode
        // switches the temp mode on
        store.dispatch(setPermModeOff);

        store.dispatch(setTempModeWpsConfig);
        TEST_ASSERT_EQUAL_INT(State::PermMode::OFF, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::TempMode::WPS_CONFIG, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(true, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
        store.dispatch(setTempModeAccessPoint);
        TEST_ASSERT_EQUAL_INT(State::PermMode::OFF, state()->permMode);
        TEST_ASSERT_EQUAL_INT(State::TempMode::ACCESS_POINT, state()->tempMode);
        TEST_ASSERT_EQUAL_INT(true, state()->tempModeActive);
        TEST_ASSERT_EQUAL_UINT32(60000, state()->accessPointTimeout);
      }

      void deserialize() {
        withObj([&](JsonObject & object) {
          object[State::MODE_FIELD] = static_cast<int>(State::PermMode::ACCESS_POINT);
          object[State::ACCESS_POINT_TIMEOUT_FIELD] = 60000;
          reducer.deserialize(object);
        });
      }

      void test() {
        RUN_TEST(testDefaults);
        RUN_TEST(testFieldNames);
        RUN_TEST(testInitialState);
        RUN_TEST(testDeserializeAction);
        RUN_TEST(testSetAccessPointTimeoutAction);
        RUN_TEST(testNextModeAction);
        RUN_TEST(testSetPermMode);
        RUN_TEST(testSetTempMode);
      }
    }

    void deserialize() {
      Manager::deserialize();
    }

    void test() {
      Manager::test();
    }
  }

  void deserialize() {
    Network::deserialize();
  }

  void initialize() {
    // initialize the reducers
    deserialize();
    // initialize the subscriber
    subscriber.state = nullptr;
    // initialize the state
    store.setup(&reducer, &subscriber);
  }

  void test() {
    Network::test();
  }
}

// // Note the case, this is not an arduino
// // function, it is the Unity setUp function
// // that runs before each test
// void setUp() {
  // Config::initialize();
// }

void setup(void) {
  UNITY_BEGIN();
  Config::test();
  UNITY_END();
}

void loop() {
}

int main(int argc, char **argv) {
  setup();
}
