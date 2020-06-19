#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    Memory::Pair<State, Params> memory;

    constexpr bool defaultOn = false;
    constexpr unsigned char defaultLevel = 0;
    constexpr unsigned char defaultPwm = 0;

    State::State(const Params * params) :
      on(params ? params->on : defaultOn),
      level(params ? params->level : defaultLevel),
      pwm(params ? params->pwm : defaultPwm)
    {}

    void State::serialize(JsonObject & object) const {
      object[onField] = on;
      object[levelField] = level;
      object[pwmField] = pwm;
    }

  }
}
