#include <Util/Debug.hpp>
#include <Config.hpp>
#include "ActionType.hpp"
#include "State.hpp"
#include "Actions.hpp"

namespace BurpDimmer {
  namespace Light {
    namespace Actions {

      void action(f_getState getState, f_onAction onAction) {
        return getState([](const Error error, const State * state) {
          if (error == Error::noError) {
            Action action(ActionType::SET_STATE, &state);
            return onAction(error, &action);
          }
          return onAction(error, nullptr);
        });
      }

      void deserialize(const JsonObject & object, f_onState onState) {
        auto lightConfig = Config::store.getState()->light;
        auto maxLevel = lightConfig->levelCount - 1;
        auto levels = lightConfig->levels;
        if (!object.isNull()) {
          // deserialize
          if (!object[onField].is<bool>()) {
            BURP_DEBUG_INFO("Error::invalidOn");
            return onState(Error::invalidOn, nullptr);
          }
          bool on = object[onField];
          if (!object[levelField].is<unsigned char>()) {
            BURP_DEBUG_INFO("Error::invalidLevel");
            return onState(Error::invalidLevel, nullptr);
          }
          unsigned char level = object[levelField];
          // we allow a null pwm field but if it is set
          // it must be valid
          if (!object[pwmField].isNull()) {
            if (!object[pwmField].is<unsigned char>()) {
              BURP_DEBUG_INFO("Error::invalidPwm");
              return onState(Error::invalidPwm, nullptr);
            }
            unsigned char pwm = object[pwmField];
            // both level and pwm are set so check them against
            // the configured levels and choose the most appropriate
            const State state(on, level, pwm);
            return applyConfig(state, onState);
          }
          // pwm is not set so validate the level
          if (level > maxLevel) {
            BURP_DEBUG_INFO("Error::outOfRange");
            return onState(Error::outOfRange, nullptr);
          }
          auto pwm = levels[level];
          const State state(on, level, pwm);
          return onState(Error::noError, &state);
        }
        BURP_DEBUG_INFO("Error::noObject");
        return onState(Error::noObject, nullptr);
      }

      void applyConfig(const State & previous, f_onState onState) {
        auto lightConfig = Config::store.getState()->light;
        auto levelCount = lightConfig->levelCount;
        auto levels = lightConfig->levels;
        // check if the pwm and level matches the current config levels
        if (previous.level < levelCount) {
          if (previous.pwm == levels[previous.level]) {
            return onState(Error::noError, &state);
          }
        }
        // pick the largest pwm less than or equal to the current pwm
        // if no level found then pick the maximum level
        // and turn the light off
        auto on = false;
        auto level = levelCount - 1;
        for (int i = 0; i < levelCount; i++) {
          if (levels[i] <= previous.pwm) {
            on = previousOn;
            level = i;
          } else {
            break;
          }
        }
        auto pwm = levels[level];
        const State state(on, level, pwm);
        return onState(Error::noError, &state);
      }

      void toggle(State & previous, f_onState onState) {
        const State state(!previous.on, previous.level, previous.pwm);
        return onState(Error::noError, &state);
      }

      void increaseBrightness(const State & previous, f_onState onState) {
        auto lightConfig = Config::store.getState()->light;
        auto maxLevel = lightConfig->levelCount - 1;
        auto levels = lightConfig->levels;
        unsigned char level;
        if (previous.on) {
          level = previous.level + 1;
          if (level > maxLevel) {
            BURP_DEBUG_INFO("Error::maxBrightness");
            return onState(Error::maxBrightness, nullptr);
          }
        } else {
          level = 0;
        }
        auto pwm = levels[level];
        const State state(true, level, pwm);
        return onState(Error::noError, &state);
      }

      void decreaseBrightness(const State & previous, f_onState onState) {
        auto lightConfig = Config::store.getState()->light;
        auto maxLevel = lightConfig->levelCount - 1;
        auto levels = lightConfig->levels;
        bool on;
        unsigned char level;
        unsigned char pwm;
        if (!previous.on) {
          BURP_DEBUG_INFO("Error::minBrightness");
          return onState(Error::minBrightness, nullptr);
        }
        if (previous.level == 0) {
          on = false;
          level = maxLevel;
        } else {
          on = true;
          level = previous.level - 1;
        }
        auto pwm = levels[level];
        const State state(on, level, pwm);
        return onState(Error::noError, &state);
      }

    }
  }
}
