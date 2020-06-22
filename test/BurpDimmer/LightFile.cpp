#include <unity.h>

// include platform for the millis() function
#include <TestHelpers/platform.hpp>

#include <BurpDimmer/LightFile.hpp>
#include "LightFile.hpp"

namespace BurpDimmerTest {
  namespace LightFile {
    Module tests("LightFile", [](Describe & describe) {
    });
  }
}
