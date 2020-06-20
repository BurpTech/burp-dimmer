#pragma once

#include <array>
#include "../../Json/Serializer.hpp"
#include "../../Memory/Pair.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      constexpr char levelsField[] = "levels";
      constexpr char saveStateDelayField[] = "saveStateDelay";
      constexpr char offLevelField[] = "offLevelField";

      // max levels is 255 and not 256 because 0 is
      // not a valid level (it is off).
      // Also this allows us to still reference the
      // last entry of the array with an unsigned char.
      // Additionally some checks in the Light state
      // assume that an unsigned char will not run off
      // the end of the array.
      constexpr unsigned char maxLevels = 255;
      // add one to max levels so that we always have a zero on the end
      // we can use to check for max brightness
      using Levels = std::array<unsigned char, maxLevels + 1>;

      struct Params {
        const Levels & levels;
        const unsigned long saveStateDelay;
        const unsigned char offLevel;
      };

      class State : public Json::Serializer {

        public:
          
          const Levels levels;
          const unsigned long saveStateDelay;
          const unsigned char offLevel;

          State(const Params * params);
          void serialize(JsonObject & object) const override;

      };

      using Memory = Memory::Pair<State, Params>;
      extern Memory memory;

    }
  }
}
