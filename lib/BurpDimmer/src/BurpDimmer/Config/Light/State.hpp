#pragma once

#include <array>
#include <BurpTree/State.hpp>
#include <BurpTree/Factory.hpp>
#include <BurpTree/Status.hpp>

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
      constexpr unsigned char maxLevels = 255;

      class State : public BurpTree::State {

        public:

          using Level = unsigned char;
          using Delay = unsigned long;

          // add one to max levels so that we always have a zero on the end
          // we can use to check for max brightness
          using Levels = std::array<Level, maxLevels + 1>;

          const Levels levels;
          const Delay saveStateDelay;
          const Level offLevel;

          State(
              const Uid uid,
              const Levels levels,
              const Delay saveStateDelay,
              const Level offLevel
          );
          State(const Uid uid);
          void serialize(const JsonObject & object) const override;

      };

      class Status : public BurpTree::Status {
        public:
          enum : BurpTree::Status::Code {
            noError,
            noObject,
            noLevels,
            noSaveStateDelay,
            noOffLevel,
            notAnArray,
            minLevels,
            maxLevels,
            invalidLevels,
            invalidSaveStateDelay,
            invalidOffLevel,
            offLevelOutOfRange,
            levelZero
          };
          const char * c_str() const override;
      };

      class Factory : public BurpTree::Factory<State, Status> {

        public:

          const BurpTree::State * deserialize(const JsonObject & serialized) override ;

        private:

          const State * _default() override;

      };

    }
  }
}
