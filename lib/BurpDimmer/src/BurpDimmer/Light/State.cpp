#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    constexpr bool defaultOn = false;
    constexpr unsigned char defaultLevel = 0;
    constexpr unsigned char defaultPwm = 0;

    State::State() :
      State(nullptr, defaultOn, defaultLevel, defaultPwm)
    {}

    State::State(const State & state) :
      State(nullptr, state.on, state.level, state.pwm)
    {}

    State::State(const State * previous, const State & next) :
      State(previous, next.on, next.level, next.pwm)
    {}

    State::State(const bool on, const unsigned char level, const unsigned char pwm) :
      State(nullptr, on, level, pwm)
    {}

    State::State(const State * previous, const bool on, const unsigned char level, const unsigned char pwm) :
      Redux::State(previous),
      on(on),
      level(level),
      pwm(pwm)
    {}

    void State::serialize(JsonObject & object) const {
      object[onField] = on;
      object[levelField] = level;
      object[pwmField] = pwm;
    }

  }
}
