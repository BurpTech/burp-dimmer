#include <BurpDebug.hpp>
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {
    namespace State {

      constexpr bool defaultOn = false;
      unsigned char defaultLevel(const Config * config) {
        return config->offLevel;
      }
      unsigned char defaultPwm(const Config * config) {
        return config->levels[defaultLevel(config)];
      }

      Instance::Instance(const Params & params, const unsigned long uid) :
        BurpRedux::State::Instance(uid),
        on(params.error == Error::noError ? params.on : defaultOn),
        level(params.error == Error::noError ? params.level : defaultLevel(params.config)),
        pwm(params.error == Error::noError ? params.pwm : defaultPwm(params.config)),
        config(params.config)
      {}

      void Instance::serialize(const JsonObject & object) const {
        object[onField] = on;
        object[levelField] = level;
        object[pwmField] = pwm;
      }

    }
  }
}
