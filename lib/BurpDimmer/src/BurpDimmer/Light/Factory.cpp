#include "Serialization.hpp"
#include "Factory.hpp"

namespace BurpDimmer {
  namespace Light {

    constexpr bool defaultOn = false;

    void Factory::setConfig(const Config * config) {
      _config = config;
    }

    bool Factory::deserialize(const JsonVariant & serialized) {
      return create([&]() -> const State * {
          Serialization serialization;
          auto code = serialization.deserialize(serialized);

          if (code == Status::ok) {
            auto levels = _config->levels;

            if (serialization.root.pwm.isNull) {
              auto pwm = levels[serialization.root.level.value];
              if (pwm == 0) {
                return error(Status::outOfRange);
              }
              return ok(new(getAddress()) State(
                serialization.root.on.value,
                serialization.root.level.value,
                serialization.root.pwm.value,
                _config->saveStateDelay
              ));
            }
            return _applyConfig(
              serialization.root.on.value,
              serialization.root.level.value,
              serialization.root.pwm.value
            );
          }

          return error(code);
      });
    }

    bool Factory::applyConfig(const Config * config) {
      return create([&]() -> const State * {
          _config = config;
          const State * previous = getState();
          return _applyConfig(
            previous->on,
            previous->level,
            previous->pwm
          );
      });
    }

    bool Factory::toggle() {
      return create([&]() -> const State * {
          const State * previous = getState();
          return ok(new(getAddress()) State(
            !previous->on,
            previous->level,
            previous->pwm,
            _config->saveStateDelay
          ));
      });
    }

    bool Factory::increaseBrightness() {
      return create([&]() -> const State * {
          const State * previous = getState();
          auto levels = _config->levels;
          LevelIndex level;
          if (previous->on) {
            level = previous->level + 1;
            // this works because the array is always one bigger
            // than the maxLevels, so even if we use all the available
            // levels there will always be a zero at the end of the array
            if (levels[level] == 0) {
              return error(Status::maxBrightness);
            }
          } else {
            level = 0;
          }
          return ok(new(getAddress()) State(
            true,
            level,
            levels[level],
            _config->saveStateDelay
          ));
      });
    }

    bool Factory::decreaseBrightness() {
      return create([&]() -> const State * {
          const State * previous = getState();
          auto levels = _config->levels;
          auto offLevel = _config->offLevel;
          bool on;
          LevelIndex level;
          if (!previous->on) {
            return error(Status::minBrightness);
          }
          if (previous->level == 0) {
            on = false;
            level = offLevel;
          } else {
            on = true;
            level = previous->level - 1;
          }
          return ok(new(getAddress()) State(
            on,
            level,
            levels[level],
            _config->saveStateDelay
          ));
      });
    }

    const State * Factory::_applyConfig(
        const bool on,
        const LevelIndex level,
        const Level pwm
    ) {
      auto levels = _config->levels;
      auto offLevel = _config->offLevel;
      // check if the pwm and level matches the current config levels
      if (pwm == levels[level]) {
        return ok(new(getAddress()) State(
          on,
          level,
          pwm,
          _config->saveStateDelay
        ));
      }
      // pick the largest pwm less than or equal to the current pwm
      // if no level found then pick the maximum level
      // and turn the light off
      auto _on = false;
      auto _level = offLevel;
      LevelIndex count = 0;
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
      return ok(new(getAddress()) State(
        _on,
        _level,
        levels[_level],
        _config->saveStateDelay
      ));
    }

    bool Factory::createDefault() {
      return create([&]() -> const State * {
          return ok(new(getAddress()) State(
            defaultOn,
            _config->offLevel,
            _config->levels[_config->offLevel],
            _config->saveStateDelay
          ));
      });
    }

  }
}
