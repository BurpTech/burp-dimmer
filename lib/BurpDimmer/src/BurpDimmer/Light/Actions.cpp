#include "../Util/Debug.hpp"
#include "../Config.hpp"
#include "Actions.hpp"

namespace BurpDimmer {
  namespace Light {

    void deserialize(const JsonObject & object, f_onParams onParams) {
      auto lightConfig = Config::store.getState()->light;
      auto maxLevel = lightConfig->levelCount - 1;
      auto levels = lightConfig->levels;
      if (!object.isNull()) {
        // deserialize
        if (!object[onField].is<bool>()) {
          BURP_DEBUG_INFO("Error::invalidOn");
          return onParams(Error::invalidOn, nullptr);
        }
        bool on = object[onField];
        if (!object[levelField].is<unsigned char>()) {
          BURP_DEBUG_INFO("Error::invalidLevel");
          return onParams(Error::invalidLevel, nullptr);
        }
        unsigned char level = object[levelField];
        // we allow a null pwm field but if it is set
        // it must be valid
        if (!object[pwmField].isNull()) {
          if (!object[pwmField].is<unsigned char>()) {
            BURP_DEBUG_INFO("Error::invalidPwm");
            return onParams(Error::invalidPwm, nullptr);
          }
          unsigned char pwm = object[pwmField];
          // both level and pwm are set so check them against
          // the configured levels and choose the most appropriate
          const Params params = {
            on,
            level,
            pwm
          };
          return applyConfig(params, onParams);
        }
        // pwm is not set so validate the level
        if (level > maxLevel) {
          BURP_DEBUG_INFO("Error::outOfRange");
          return onParams(Error::outOfRange, nullptr);
        }
        auto pwm = levels[level];
        const Params params = {
          on,
          level,
          pwm
        };
        return onParams(Error::noError, &params);
      }
      BURP_DEBUG_INFO("Error::noObject");
      return onParams(Error::noObject, nullptr);
    }

    void applyConfig(const Params & previous, f_onParams onParams) {
      auto lightConfig = Config::store.getState()->light;
      auto levelCount = lightConfig->levelCount;
      auto levels = lightConfig->levels;
      // check if the pwm and level matches the current config levels
      if (previous.level < levelCount) {
        if (previous.pwm == levels[previous.level]) {
          return onParams(Error::noError, &previous);
        }
      }
      // pick the largest pwm less than or equal to the current pwm
      // if no level found then pick the maximum level
      // and turn the light off
      auto on = false;
      auto level = levelCount - 1;
      for (int i = 0; i < levelCount; i++) {
        if (levels[i] <= previous.pwm) {
          on = previous.on;
          level = i;
        } else {
          break;
        }
      }
      auto pwm = levels[level];
      const Params params = {
        on,
        level,
        pwm
      };
      return onParams(Error::noError, &params);
    }

    void applyConfig(const State * previous, f_onParams onParams) {
      const Params params = {
        previous->on,
        previous->level,
        previous->pwm
      };
      applyConfig(params, onParams);
    }

    void toggle(State * previous, f_onParams onParams) {
      const Params params = {
        !previous->on,
        previous->level,
        previous->pwm
      };
      return onParams(Error::noError, &params);
    }

    void increaseBrightness(const State * previous, f_onParams onParams) {
      auto lightConfig = Config::store.getState()->light;
      auto maxLevel = lightConfig->levelCount - 1;
      auto levels = lightConfig->levels;
      unsigned char level;
      if (previous->on) {
        level = previous->level + 1;
        if (level > maxLevel) {
          BURP_DEBUG_INFO("Error::maxBrightness");
          return onParams(Error::maxBrightness, nullptr);
        }
      } else {
        level = 0;
      }
      auto pwm = levels[level];
      const Params params = {true, level, pwm};
      return onParams(Error::noError, &params);
    }

    void decreaseBrightness(const State * previous, f_onParams onParams) {
      auto lightConfig = Config::store.getState()->light;
      auto maxLevel = lightConfig->levelCount - 1;
      auto levels = lightConfig->levels;
      bool on;
      unsigned char level;
      if (!previous->on) {
        BURP_DEBUG_INFO("Error::minBrightness");
        return onParams(Error::minBrightness, nullptr);
      }
      if (previous->level == 0) {
        on = false;
        level = maxLevel;
      } else {
        on = true;
        level = previous->level - 1;
      }
      auto pwm = levels[level];
      const Params params = {on, level, pwm};
      return onParams(Error::noError, &params);
    }

  }
}
