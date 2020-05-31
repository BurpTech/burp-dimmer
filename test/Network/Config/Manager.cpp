#ifndef NATIVE
#include <Arduino.h>
#endif

#include <unity.h>

class JsonObject {
};

#include "../src/Network/Config/Manager.hpp"

using namespace Network::Config;
Manager manager;

void test() {
  TEST_ASSERT_EQUAL_INT(Manager::Mode::NORMAL, manager.mode);
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test);
  UNITY_END();
}

void loop() {
}

int main() {
  setup();
}
