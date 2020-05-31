#ifndef NATIVE
#include <Arduino.h>
#endif

#include <unity.h>
#include <functional>
#include <ArduinoJson.hpp>

#include "../../src/Config/Network/Manager.hpp"
#include "../../src/Redux/Store.hpp"

using namespace Redux;
using namespace Config;
using namespace Network;

Store<ActionType> store;

class TestSubscriber : public Subscriber {
  public:
    const Manager * manager;

    TestSubscriber() :
      manager(nullptr) {
    }

    void notify() override {
      manager = store.getState<Manager>();
    }
};

const ManagerReducer reducer;
TestSubscriber subscriber;

using f_onObj = std::function<void(JsonObject & obj)>;
void withObj(f_onObj onObj) {
  StaticJsonDocument<50> doc;
  JsonObject obj = doc.to<JsonObject>();
  onObj(obj);
}

void testManagerSerialization() {
  Manager manager;
  TEST_ASSERT_EQUAL_INT(Manager::Mode::NORMAL, manager.mode);
  withObj([&](JsonObject & obj) {
    obj[Manager::MODE_FIELD] = static_cast<int>(Manager::Mode::ACCESS_POINT);
    manager.deserialize(obj);
    TEST_ASSERT_EQUAL_INT(Manager::Mode::ACCESS_POINT, manager.mode);
  });
  withObj([&](JsonObject & obj) {
    manager.serialize(obj);
    TEST_ASSERT_EQUAL_INT(Manager::Mode::ACCESS_POINT, obj[Manager::MODE_FIELD].as<int>());
  });
}

void testManagerReducer() {
  TEST_ASSERT_NULL(subscriber.manager);
  store.setup(&reducer, &subscriber);
  TEST_ASSERT_NOT_NULL(subscriber.manager);
  TEST_ASSERT_EQUAL_INT(Manager::Mode::NORMAL, subscriber.manager->mode);
  const Manager * manager = subscriber.manager;
  ManagerSetModeAction action(Manager::Mode::OFF);
  store.dispatch(action);
  TEST_ASSERT(manager != subscriber.manager);
  TEST_ASSERT_EQUAL_INT(Manager::Mode::OFF, subscriber.manager->mode);
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(testManagerSerialization);
  RUN_TEST(testManagerReducer);
  UNITY_END();
}

void loop() {
}

int main(int argc, char **argv) {
  setup();
}
