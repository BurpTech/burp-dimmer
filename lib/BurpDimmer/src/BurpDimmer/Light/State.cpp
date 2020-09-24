#include "Serialization.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    State::State(
        const bool on,
        const LevelIndex level,
        const Level pwm,
        const Delay saveStateDelay
    ) :
      on(on),
      level(level),
      pwm(pwm),
      saveStateDelay(saveStateDelay)
    {}

    bool State::serialize(const JsonVariant & serialized) const {
      Serialization serialization;
      serialization.root.on.value = on;
      serialization.root.level.value = level;
      serialization.root.pwm.value = pwm;
      return serialization.serialize(serialized);
    }

  }
}
