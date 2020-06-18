#include <unity.h>
#include <BddUnity.hpp>

#include "Redux.hpp"
#include "Config.hpp"

Runnable * runnables[] = {
  &Redux::tests,
  &Config::tests,
  nullptr
};

Runner runner(runnables);
Memory memory;
bool running = true;
int status;

void setup() {
  UNITY_BEGIN();
  runner.setup(memory);
}

void loop() {
  if (running) {
    runner.loop();
    if (runner.isFinished()) {
      status = UNITY_END();
      running = false;
    }
  }
}

int main() {
  setup();
  while (running) {
    loop();
  }
  return status;
}
