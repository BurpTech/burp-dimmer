#include "Serialization.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      State::State(
          const Levels levels,
          const Delay saveStateDelay,
          const LevelIndex offLevel
      ) :
        levels(levels),
        saveStateDelay(saveStateDelay),
        offLevel(offLevel)
      {}

      bool State::serialize(const JsonVariant & serialized) const {
        Serialization serialization;
        serialization.root.levels.list = levels;
        serialization.root.saveStateDelay.value = saveStateDelay;
        serialization.root.offLevel.value = offLevel;
        return serialization.serialize(serialized);
      }

    }
  }
}
