#ifndef NATIVE
#include <Arduino.h>
#endif

#include <unity.h>
#include <functional>

#include "../src/Network/Config/Manager.hpp"
#include "ArduinoJson.hpp"

using namespace Network::Config;
Manager manager;

using f_onObj = std::function<void(JsonObject & obj)>;
void withObj(f_onObj onObj) {
  StaticJsonDocument<50> doc;
  JsonObject obj = doc.to<JsonObject>();
  onObj(obj);
}

void testManager() {
  TEST_ASSERT_EQUAL_INT(Manager::Mode::NORMAL, manager.mode);
  withObj([](JsonObject & obj) {
    obj[Manager::MODE_FIELD] = static_cast<int>(Manager::Mode::ACCESS_POINT);
    manager.deserialize(obj);
    TEST_ASSERT_EQUAL_INT(Manager::Mode::ACCESS_POINT, manager.mode);
  });
  withObj([](JsonObject & obj) {
    manager.serialize(obj);
    TEST_ASSERT_EQUAL_INT(Manager::Mode::ACCESS_POINT, obj[Manager::MODE_FIELD].as<int>());
  });
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(testManager);
  UNITY_END();
}

void loop() {
}

int main(int argc, char **argv) {
  setup();
}
