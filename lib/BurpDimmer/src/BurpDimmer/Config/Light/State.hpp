#pragma once

#include <array>
#include <BurpTree/State.hpp>
#include "Types.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      class State : public BurpTree::State {

        public:

          const Levels levels;
          const Delay saveStateDelay;
          const LevelIndex offLevel;

          State(
              const Levels levels,
              const Delay saveStateDelay,
              const LevelIndex offLevel
          );
          bool serialize(const JsonVariant & object) const override;

      };

    }
  }
}
