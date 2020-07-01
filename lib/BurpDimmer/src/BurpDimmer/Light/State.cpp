#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    constexpr char onField[] = "on";
    constexpr char levelField[] = "level";
    constexpr char pwmField[] = "pwm";

    constexpr bool defaultOn = false;
    unsigned char defaultLevel(const Config * config) {
      return config->offLevel;
    }
    unsigned char defaultPwm(const Config * config) {
      return config->levels[config->offLevel];
    }

    State::State(
        const Uid uid,
        const Config * config,
        const bool on,
        const Level level,
        const Pwm pwm
    ) :
      BurpTree::State(uid),
      config(config),
      on(on),
      level(level),
      pwm(pwm)
    {}

    State::State(const Uid uid, const Config * config) :
      State(uid, config, defaultOn, defaultLevel(config), defaultPwm(config))
    {}

    void State::serialize(const JsonObject & object) const {
      object[onField] = on;
      object[levelField] = level;
      object[pwmField] = pwm;
    }

    void Factory::setConfig(const Config * config) {
      _config = config;
    }

    const BurpTree::State * Factory::deserialize(const JsonObject & object) {
      return create([&]() -> const State * {
          const State * previous = getState();
          auto config = previous ? previous->config : _config;
          auto levels = config->levels;
          if (!object.isNull()) {
            // deserialize
            if (!object[onField].is<bool>()) {
              return fail(Status::invalidOn);
            }
            bool on = object[onField];
            if (!object[levelField].is<State::Level>()) {
              return fail(Status::invalidLevel);
            }
            State::Level level = object[levelField];
            // we allow a null pwm field but if it is set
            // it must be valid
            if (!object[pwmField].isNull()) {
              if (!object[pwmField].is<State::Pwm>()) {
                return fail(Status::invalidPwm);
              }
              State::Pwm pwm = object[pwmField];
              // both level and pwm are set so check them against
              // the configured levels and choose the most appropriate
              return _applyConfig(on, level, pwm);
            }
            // pwm is not set so validate the level.
            // We can just check for a zero level as the levels array
            // is always 256 entries so level cannot be off the end of
            // the array
            auto pwm = levels[level];
            if (pwm == 0) {
              return fail(Status::outOfRange);
            }
            return new(getAddress()) State(getUid(), config, on, level, pwm);
          }
          return fail(Status::noObject);
      });
    }

    const BurpTree::State * Factory::applyConfig(const Config * config) {
      return create([&]() -> const State * {
          _config = config;
          const State * previous = getState();
          return _applyConfig(previous->on, previous->level, previous->pwm);
      });
    }

    const BurpTree::State * Factory::toggle() {
      return create([&]() -> const State * {
          const State * previous = getState();
          return new(getAddress()) State(getUid(), previous->config, !previous->on, previous->level, previous->pwm);
      });
    }

    const BurpTree::State * Factory::increaseBrightness() {
      return create([&]() -> const State * {
          const State * previous = getState();
          auto config = previous->config;
          auto levels = config->levels;
          State::Level level;
          if (previous->on) {
            level = previous->level + 1;
            // this works because the array is always one bigger
            // than the maxLevels, so even if we use all the available
            // levels there will always be a zero at the end of the array
            if (levels[level] == 0) {
              return fail(Status::maxBrightness);
            }
          } else {
            level = 0;
          }
          return new(getAddress()) State(getUid(), config, true, level, levels[level]);
      });
    }

    const BurpTree::State * Factory::decreaseBrightness() {
      return create([&]() -> const State * {
          const State * previous = getState();
          auto config = previous->config;
          auto levels = config->levels;
          auto offLevel = config->offLevel;
          bool on;
          State::Level level;
          if (!previous->on) {
            return fail(Status::minBrightness);
          }
          if (previous->level == 0) {
            on = false;
            level = offLevel;
          } else {
            on = true;
            level = previous->level - 1;
          }
          return new(getAddress()) State(getUid(), config, on, level, levels[level]);
      });
    }

    const State * Factory::_applyConfig(
        const bool on,
        const State::Level level,
        const State::Pwm pwm
    ) {
      auto levels = _config->levels;
      auto offLevel = _config->offLevel;
      // check if the pwm and level matches the current config levels
      if (pwm == levels[level]) {
        return new(getAddress()) State(getUid(), _config, on, level, pwm);
      }
      // pick the largest pwm less than or equal to the current pwm
      // if no level found then pick the maximum level
      // and turn the light off
      auto _on = false;
      auto _level = offLevel;
      State::Level count = 0;
      for (auto _pwm : levels) {
        if (_pwm == 0) {
          // no more levels
          break;
        }
        if (_pwm <= pwm) {
          _on = on;
          _level = count;
          count++;
        } else {
          break;
        }
      }
      return new(getAddress()) State(getUid(), _config, _on, _level, levels[_level]);
    }

    const State * Factory::_default() {
      return new(getAddress()) State(getUid(), _config);
    }

    #define C_STR_LABEL "BurpDimmer::Light"
    #define C_STR_CASE(CODE) BURP_TREE_C_STR_CASE(C_STR_LABEL, CODE)
    #define C_STR_DEFAULT BURP_TREE_C_STR_DEFAULT(C_STR_LABEL)
    const char * Status::c_str() const {
      switch (getCode()) {
        C_STR_CASE(noError);
        C_STR_CASE(noObject);
        C_STR_CASE(maxLevels);
        C_STR_CASE(outOfRange);
        C_STR_CASE(invalidOn);
        C_STR_CASE(invalidLevel);
        C_STR_CASE(invalidPwm);
        C_STR_CASE(maxBrightness);
        C_STR_CASE(minBrightness);
        C_STR_DEFAULT;
      }
    }

  }
}
