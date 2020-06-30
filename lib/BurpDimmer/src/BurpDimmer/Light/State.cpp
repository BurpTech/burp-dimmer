#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

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

    void Factory::setInitialConfig(const Config * config) {
      _initialConfig = config;
    }

    const BurpTree::Status & Factory::getStatus() const {
      return _status;
    }

    const BurpTree::State * Factory::deserialize(const JsonObject & object) {
      return _create([&](const Uid uid, void * address) {
          _status.set(Status::Level::INFO, Status::noError);
          auto config = _previous ? _previous->config : _initialConfig;
          auto levels = config->levels;
          if (!object.isNull()) {
            // deserialize
            if (!object[onField].is<bool>()) {
              return _fail(uid, address, Status::invalidOn);
            }
            bool on = object[onField];
            if (!object[levelField].is<State::Level>()) {
              return _fail(uid, address, Status::invalidLevel);
            }
            State::Level level = object[State::levelField];
            // we allow a null pwm field but if it is set
            // it must be valid
            if (!object[pwmField].isNull()) {
              if (!object[pwmField].is<State::Pwm>()) {
                return _fail(uid, address, Status::invalidPwm);
              }
              State::Pwm pwm = object[State::pwmField];
              // both level and pwm are set so check them against
              // the configured levels and choose the most appropriate
              return applyConfig(uid, address, config, on, level, pwm);
            }
            // pwm is not set so validate the level.
            // We can just check for a zero level as the levels array
            // is always 256 entries so level cannot be off the end of
            // the array
            auto pwm = levels[level];
            if (pwm == 0) {
              return _fail(uid, address, Status::outOfRange);
            }
            return new(address) State(uid, config, on, level, pwm);
          }
          return _fail(uid, address, Status::noObject);
      });
    }

    const BurpTree::State * Factory::applyConfig(const Config * config) {
      return _create([&](const Uid uid, void * address) {
          _status.set(Status::Level::INFO, Status::noError);
          return _applyConfig(uid, address, config, _previous->on, _previous->level, _previous->pwm);
      });
    }

    const BurpTree::State * toggle() {
      return _create([&](const Uid uid, void * address) {
          _status.set(Status::Level::INFO, Status::noError);
          return new(address) State(uid, _previous->config, !_previous->on, _previous->level, _previous->pwm);
      });
    }

    const BurpTree::State * Factory::increaseBrightness() {
      return _create([&](const Uid uid, void * address) {
          _status.set(Status::Level::INFO, Status::noError);
          auto config = _previous->config;
          auto levels = config->levels;
          State::Level level;
          if (_previous->on) {
            level = _previous->level + 1;
            // this works because the array is always one bigger
            // than the maxLevels, so even if we use all the available
            // levels there will always be a zero at the end of the array
            if (levels[level] == 0) {
              _status.set(Status::Level::ERROR, Status::maxBrightness);
              return nullptr;
            }
          } else {
            level = 0;
          }
          return new(address) State(uid, config, true, level, levels[level]);
      });
    }

    const BurpTree::State * Factory::decreaseBrightness() {
      return _create([&](const Uid uid, void * address) {
          _status.set(Status::Level::INFO, Status::noError);
          auto config = _previous->config;
          auto levels = config->levels;
          auto offLevel = config->offLevel;
          bool on;
          State::Level level;
          if (!_previous->on) {
            _status.set(Status::Level::ERROR, Status::minBrightness);
            return nullptr;
          }
          if (_previous->level == 0) {
            on = false;
            level = offLevel;
          } else {
            on = true;
            level = _previous->level - 1;
          }
          return new(address) State(uid, config, on, level, levels[level]);
      });
    }

    const char * Factory::Status::c_str() const {
      switch (getCode()) {
        case noError:
          return "BurpDimmer::Light::Factory : no error";
        case noObject:
          return "BurpDimmer::Light::Factory : no object";
        case maxLevels:
          return "BurpDimmer::Light::Factory : max levels";
        case outOfRange:
          return "BurpDimmer::Light::Factory : out of range";
        case invalidOn:
          return "BurpDimmer::Light::Factory : invalid on";
        case invalidLevel:
          return "BurpDimmer::Light::Factory : invalid level";
        case invalidPwm:
          return "BurpDimmer::Light::Factory : invalid pwm";
        case maxBrightness:
          return "BurpDimmer::Light::Factory : max brightness";
        case minBrightness:
          return "BurpDimmer::Light::Factory : min brightness";
        default:
          return "BurpDimmer::Light::Factory : unknown";
    }

    const BurpTree::State * Factory::_applyConfig(
        const Uid uid,
        void * address,
        const Config * config,
        const bool on,
        const State::Level level,
        const State::Pwm pwm
    )
      auto levels = config->levels;
      auto offLevel = config->offLevel;
      // check if the pwm and level matches the current config levels
      if (pwm == levels[level]) {
        return new(address) State(uid, config, on, level, pwm);
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
      return new(address) State(uid, config, _on, _level, levels[_level]);
    }

    const BurpTree::State * Factory::_fail(const Uid uid, void * address, const Status::Code code) {
      if (_previous) {
        _status.set(Status::Level::ERROR, code);
        return nullptr;
      }
      _status.set(Status::Level::WARNING, code);
      return new(address) State(uid);
    }

  }
}
