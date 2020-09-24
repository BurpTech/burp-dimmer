#pragma once

#include <stdint.h>
#include <array>

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      // max levels is 255 and not 256 because 0 is
      // not a valid level (it is off).
      // Also this allows us to still reference the
      // last entry of the array with an unsigned char.
      // Additionally some checks in the Light state
      // assume that an unsigned char will not run off
      // the end of the array.
      constexpr size_t maxLevels = UINT8_MAX;

      using Level = uint8_t;
      using LevelIndex = uint8_t;
      using Delay = uint32_t;

      // add one to max levels so that we always have a zero on the end
      // we can use to check for max brightness
      using Levels = std::array<Level, maxLevels + 1>;

    }
  }
}