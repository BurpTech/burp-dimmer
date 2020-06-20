#include <unity.h>
#include "Light/State.hpp"

namespace BurpDimmerTest {
  namespace Light {
    Module tests("Light", [](Describe & describe) {

      describe.include(State::tests);

    });
  }
}
