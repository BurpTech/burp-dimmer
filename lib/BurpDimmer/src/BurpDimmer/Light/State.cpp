#include <BurpDimmer/Util/Debug.hpp>
#include "../Config.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    Memory::Pair<State, Params> memory;

    constexpr bool defaultOn = false;
    unsigned char defaultLevel() {
      return Config::store.getState()->light->offLevel;
    }
    unsigned char defaultPwm() {
      return Config::store.getState()->light->levels[defaultLevel()];
    }

    State::State(const Params * params) :
      on(params ? params->on : defaultOn),
      level(params ? params->level : defaultLevel()),
      pwm(params ? params->pwm : defaultPwm())
    {}

    void State::serialize(JsonObject & object) const {
      BURP_DEBUG_INFO("Serializing light state: %d: %u: %u", on, level, pwm);
      object[onField] = on;
      object[levelField] = level;
      object[pwmField] = pwm;
    }

  }
}
