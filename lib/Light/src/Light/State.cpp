#include <Config.hpp>
#include <Util/Debug.hpp>
#include "State.hpp"

namespace Light {

  constexpr char onField[] = "on";
  constexpr char levelField[] = "level";
  constexpr char pwmField[] = "pwm";

  constexpr bool defaultOn = false;
  // default pwm and level will depend on the current
  // levels config but they will be the max brightness


  State::State(const State & previous, bool on) :
    lastError(Error::noError),
    on(on),
    pwm(previous.pwm),
    level(previous.level)
  {}

  State::State(const State & previous, unsigned char level) { 
    auto lightConfig = Config::store.getState()->light;
    auto levelCount = lightConfig->levelCount;
    auto levels = lightConfig->levels;
    if (level < levelCount) {
      lastError = Error::noError;
      on = true;
      level = level;
      pwm = levels[level];
      return;
    }
    lastError = Error::outOfRange;
    on = previous.on;
    level = previous.level;
    pwm = previous.pwm;
  }

  State::State(const State & previous, Change change) {
    auto lightConfig = Config::store.getState()->light;
    auto maxLevel = lightConfig->levelCount - 1;
    auto levels = lightConfig->levels;
    lastError = Error::noError;
    switch (change) {
      case Change::decrease:
        {
          if (on) {
            if (level == 0) {
              on = false;
              level = maxLevel;
              pwm = levels[level];
              return;
            }
            level--;
            pwm = levels[level];
          }
        }
        return;
      case Change::increase:
        {
          on = true;
          level++;
          if (level > maxLevel) level = maxLevel;
          pwm = levels[level];
        }
        return;
    }
  }

  State::State(const State & previous) {
    lastError = Error::noError;
    _applyConfig(previous.on, previous.level, previous.pwm);
  }

  State::State(const State * previous, const JsonObject & object) {
    // set up the defaults
    auto lightConfig = Config::store.getState()->light;
    auto maxLevel = lightConfig->levelCount - 1;
    auto levels = lightConfig->levels;
    lastError = Error::noError;
    on = previous ? previous->on : defaultOn;
    level = previous ? previous->level : maxLevel;
    pwm = previous ? previous->pwm : levels[level];
    if (!object.isNull()) {
      // deserialize
      if (!object[onField].is<bool>()) {
        BURP_DEBUG_INFO("Error::invalidOn");
        lastError = Error::invalidOn;
        return;
      }
      auto newOn = object[onField];
      if (!object[levelField].is<unsigned char>()) {
        BURP_DEBUG_INFO("Error::invalidLevel");
        lastError = Error::invalidLevel;
        return;
      }
      auto newLevel = object[levelField];
      // we allow a null pwm field but if it is set
      // it must be valid
      if (!object[pwmField].isNull()) {
        if (!object[pwmField].is<unsigned char>()) {
          BURP_DEBUG_INFO("Error::invalidPwm");
          lastError = Error::invalidPwm;
          return;
        }
        auto newPwm = object[pwmField];
        // both level and pwm are set so check them against
        // the configured levels and choose the most appropriate
        _applyConfig(newOn, newLevel, newPwm);
        return;
      }
      // pwm is not set so validate the level
      if (newLevel > maxLevel) {
        BURP_DEBUG_INFO("Error::outOfRange");
        lastError = Error::outOfRange;
        return;
      }
      on = newOn;
      level = newLevel;
      pwm = levels[level]; 
    }
  }

  void State::serialize(JsonObject & object) const {
    object[onField] = on;
    object[levelField] = level;
    object[pwmField] = pwm;
  }

  void State::_applyConfig(const bool previousOn, const unsigned char previousLevel, const unsigned char previousPwm) {
    auto lightConfig = Config::store.getState()->light;
    auto levelCount = lightConfig->levelCount;
    auto levels = lightConfig->levels;
    // check if the pwm and level matches the current config levels
    if (previousLevel < levelCount) {
      if (previousPwm == levels[previousLevel]) {
        on = previousOn;
        level = previousLevel;
        pwm = previousPwm;
        return;
      }
    }
    // pick the largest pwm less than or equal to the current pwm
    // if no level found then pick the maximum level
    // and turn the light off
    on = false;
    level = levelCount - 1;
    for (int i = 0; i < levelCount; i++) {
      if (levels[i] <= previousPwm) {
        on = previousOn;
        level = i;
      } else {
        break;
      }
    }
    pwm = levels[level];
  }

}
