#include "../Util/Debug.hpp"
#include "Actions.hpp"

namespace BurpDimmer {
  namespace Light {

    void onFields(f_onParams onParams, const Error error, const Config * config, const State::Fields * fields) {
      const State::Params params = {
        config,
        fields
      };
      return onParams(error, &params);
    }

    void applyConfig(const State::Fields & previous, const Config * config, f_onParams onParams) {
      auto levels = config->levels;
      auto offLevel = config->offLevel;
      // check if the pwm and level matches the current config levels
      if (previous.pwm == levels[previous.level]) {
        return onFields(onParams, Error::noError, config, &previous);
      }
      // pick the largest pwm less than or equal to the current pwm
      // if no level found then pick the maximum level
      // and turn the light off
      auto on = false;
      unsigned char level = offLevel;
      unsigned char count = 0;
      for (auto pwm : levels) {
        if (pwm == 0) {
          // no more levels
          break;
        }
        if (pwm <= previous.pwm) {
          on = previous.on;
          level = count;
          count++;
        } else {
          break;
        }
      }
      auto pwm = levels[level];
      const State::Fields fields = {
        on,
        level,
        pwm
      };
      return onFields(onParams, Error::noError, config, &fields);
    }

    void deserialize(const JsonObject & object, const Config * config, f_onParams onParams) {
      auto levels = config->levels;
      if (!object.isNull()) {
        // deserialize
        if (!object[State::onField].is<bool>()) {
          BURP_DEBUG_INFO("Error::invalidOn");
          return onFields(onParams, Error::invalidOn, config, nullptr);
        }
        bool on = object[State::onField];
        if (!object[State::levelField].is<unsigned char>()) {
          BURP_DEBUG_INFO("Error::invalidLevel");
          return onFields(onParams, Error::invalidLevel, config, nullptr);
        }
        unsigned char level = object[State::levelField];
        // we allow a null pwm field but if it is set
        // it must be valid
        if (!object[State::pwmField].isNull()) {
          if (!object[State::pwmField].is<unsigned char>()) {
            BURP_DEBUG_INFO("Error::invalidPwm");
            return onFields(onParams, Error::invalidPwm, config, nullptr);
          }
          unsigned char pwm = object[State::pwmField];
          // both level and pwm are set so check them against
          // the configured levels and choose the most appropriate
          const State::Fields fields = {
            on,
            level,
            pwm
          };
          return applyConfig(fields, config, onParams);
        }
        // pwm is not set so validate the level.
        // We can just check for a zero level as the levels array
        // is always 256 entries so level cannot be off the end of
        // the array
        auto pwm = levels[level];
        if (pwm == 0) {
          BURP_DEBUG_INFO("Error::outOfRange");
          return onFields(onParams, Error::outOfRange, config, nullptr);
        }
        const State::Fields fields = {
          on,
          level,
          pwm
        };
        return onFields(onParams, Error::noError, config, &fields);
      }
      BURP_DEBUG_INFO("Error::noObject");
      return onFields(onParams, Error::noObject, config, nullptr);
    }

    void applyConfig(const State::Instance * previous, const Config * config, f_onParams onParams) {
      const State::Fields fields = {
        previous->on,
        previous->level,
        previous->pwm
      };
      applyConfig(fields, config, onParams);
    }

    void toggle(const State::Instance * previous, f_onParams onParams) {
      const State::Fields fields = {
        !previous->on,
        previous->level,
        previous->pwm
      };
      return onFields(onParams, Error::noError, previous->config, &fields);
    }

    void increaseBrightness(const State::Instance * previous, f_onParams onParams) {
      auto levels = previous->config->levels;
      unsigned char level;
      if (previous->on) {
        level = previous->level + 1;
        // this works because the array is always one bigger
        // than the maxLevels, so even if we use all the available
        // levels there will always be a zero at the end of the array
        if (levels[level] == 0) {
          BURP_DEBUG_INFO("Error::maxBrightness");
          return onFields(onParams, Error::maxBrightness, previous->config, nullptr);
        }
      } else {
        level = 0;
      }
      auto pwm = levels[level];
      const State::Fields fields = {
        true,
        level,
        pwm
      };
      return onFields(onParams, Error::noError, previous->config, &fields);
    }

    void decreaseBrightness(const State::Instance * previous, f_onParams onParams) {
      auto levels = previous->config->levels;
      auto offLevel = previous->config->offLevel;
      bool on;
      unsigned char level;
      if (!previous->on) {
        BURP_DEBUG_INFO("Error::minBrightness");
        return onFields(onParams, Error::minBrightness, previous->config, nullptr);
      }
      if (previous->level == 0) {
        on = false;
        level = offLevel;
      } else {
        on = true;
        level = previous->level - 1;
      }
      auto pwm = levels[level];
      const State::Fields fields = {
        on,
        level,
        pwm
      };
      return onFields(onParams, Error::noError, previous->config, &fields);
    }

  }
}
