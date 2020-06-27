#include <BurpDebug.hpp>
#include "Actions.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    void applyConfig(State::Params & params) {
      auto levels = params.config->levels;
      auto offLevel = params.config->offLevel;
      // check if the pwm and level matches the current config levels
      if (params.pwm == levels[params.level]) {
        return;
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
        if (pwm <= params.pwm) {
          on = params.on;
          level = count;
          count++;
        } else {
          break;
        }
      }
      auto pwm = levels[level];
      params.on = on;
      params.level = level;
      params.pwm = pwm;
    }

    void deserialize(const JsonObject & object, State::Params & params) {
      params.error = State::Error::noError;
      auto levels = params.config->levels;
      if (!object.isNull()) {
        // deserialize
        if (!object[State::onField].is<bool>()) {
          BURP_DEBUG_INFO("Error::invalidOn");
          params.error = State::Error::invalidOn;
          return;
        }
        bool on = object[State::onField];
        if (!object[State::levelField].is<unsigned char>()) {
          BURP_DEBUG_INFO("Error::invalidLevel");
          params.error = State::Error::invalidLevel;
          return;
        }
        unsigned char level = object[State::levelField];
        // we allow a null pwm field but if it is set
        // it must be valid
        if (!object[State::pwmField].isNull()) {
          if (!object[State::pwmField].is<unsigned char>()) {
            BURP_DEBUG_INFO("Error::invalidPwm");
            params.error = State::Error::invalidPwm;
            return;
          }
          unsigned char pwm = object[State::pwmField];
          // both level and pwm are set so check them against
          // the configured levels and choose the most appropriate
          params.on = on;
          params.level = level;
          params.pwm = pwm;
          return applyConfig(params);
        }
        // pwm is not set so validate the level.
        // We can just check for a zero level as the levels array
        // is always 256 entries so level cannot be off the end of
        // the array
        auto pwm = levels[level];
        if (pwm == 0) {
          BURP_DEBUG_INFO("Error::outOfRange");
          params.error = State::Error::outOfRange;
          return;
        }
        params.on = on;
        params.level = level;
        params.pwm = pwm;
        return;
      }
      BURP_DEBUG_INFO("Error::noObject");
      params.error = State::Error::noObject;
    }

    void applyConfig(const State::Instance * previous, const Config * config, State::Params & params) {
      params.error = State::Error::noError,
      params.config = config;
      params.on = previous->on;
      params.level = previous->level;
      params.pwm = previous->pwm;
      applyConfig(params);
    }

    void toggle(const State::Instance * previous, State::Params & params) {
      params.error = State::Error::noError;
      params.config = previous->config;
      params.on = !previous->on;
      params.level = previous->level;
      params.pwm = previous->pwm;
    }

    void increaseBrightness(const State::Instance * previous, State::Params & params) {
      params.error = State::Error::noError;
      params.config = previous->config;
      auto levels = previous->config->levels;
      unsigned char level;
      if (previous->on) {
        level = previous->level + 1;
        // this works because the array is always one bigger
        // than the maxLevels, so even if we use all the available
        // levels there will always be a zero at the end of the array
        if (levels[level] == 0) {
          BURP_DEBUG_INFO("Error::maxBrightness");
          params.error = State::Error::maxBrightness;
          return;
        }
      } else {
        level = 0;
      }
      auto pwm = levels[level];
      params.on = true;
      params.level = level;
      params.pwm = pwm;
    }

    void decreaseBrightness(const State::Instance * previous, State::Params & params) {
      params.error = State::Error::noError;
      params.config = previous->config;
      auto levels = previous->config->levels;
      auto offLevel = previous->config->offLevel;
      bool on;
      unsigned char level;
      if (!previous->on) {
        BURP_DEBUG_INFO("Error::minBrightness");
        params.error = State::Error::minBrightness;
        return;
      }
      if (previous->level == 0) {
        on = false;
        level = offLevel;
      } else {
        on = true;
        level = previous->level - 1;
      }
      auto pwm = levels[level];
      params.on = on;
      params.level = level;
      params.pwm = pwm;
    }

  }
}
