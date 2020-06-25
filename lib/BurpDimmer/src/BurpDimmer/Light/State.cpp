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

      Instance::Instance(const Params * params, unsigned long sequenceId) :
        on(params->fields ? params->fields->on : defaultOn),
        level(params->fields ? params->fields->level : defaultLevel(params->config)),
        pwm(params->fields ? params->fields->pwm : defaultPwm(params->config)),
        config(params->config),
        sequenceId(sequenceId)
      {}

      void Instance::serialize(JsonObject & object) const {
        BURP_DEBUG_INFO(
          "Serializing light state: %s: %d: %s: %u: %s: %u",
          onField,
          on,
          levelField,
          level,
          pwmField,
          pwm
        );
        auto ret = object[onField].set(on);
        BURP_DEBUG_INFO("Set on field: %d", ret);
        object[levelField] = level;
        object[pwmField] = pwm;
      }

      unsigned long Instance::getUid() const {
        return sequenceId;
      }

    }
  }
}
