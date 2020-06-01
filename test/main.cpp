#ifndef NATIVE
#include <Arduino.h>
#endif

#include <unity.h>

#include "./lib/Redux.hpp"
#include "./lib/Config.hpp"

void setup(void) {
  UNITY_BEGIN();
  Redux::test();
  Config::test();
  UNITY_END();
}

void loop() {
}

int main(int argc, char **argv) {
  setup();
}
