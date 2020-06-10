#ifndef NATIVE
#include <Arduino.h>
#endif

#include <unity.h>
#include <BddUnity.hpp>

#include "./lib/Redux.hpp"
#include "./lib/Config.hpp"

bool running = true;
Memory memory;
Module * modules[] = {
  &(Redux::tests),
  // config,
  nullptr
};
Runner runner(modules);

void setup(void) {
  UNITY_BEGIN();
}

void loop() {
  if (runner.isRunning()) {
    runner.loop();
  } else  {
    running = false;
    UNITY_END();
  }
}

int main(int argc, char **argv) {
  setup();
  while (running) {
    loop();
  }
}
