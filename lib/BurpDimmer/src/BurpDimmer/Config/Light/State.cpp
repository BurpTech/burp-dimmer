#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      constexpr Levels defaultLevels = {
        10,
        20,
        31,
        41,
        51,
        61,
        71,
        82,
        92,
        102,
        112,
        122,
        133,
        143,
        153,
        163,
        173,
        184,
        194,
        204,
        214,
        224,
        235,
        245,
        255
      };
      constexpr unsigned long defaultSaveStateDelay = 5000;
      constexpr unsigned char defaultOffLevel = 24;

      State::State(
          const Uid uid,
          const Levels levels,
          const Delay saveStateDelay,
          const Level offLevel
      ) :
        BurpTree::State(uid),
        levels(levels),
        saveStateDelay(saveStateDelay),
        offLevel(offLevel)
      {}

      State::State(const Uid uid) :
        State(uid, defaultLevels, defaultSaveStateDelay, defaultOffLevel)
      {}

      void State::serialize(const JsonObject & object) const {
        JsonArray array = object[levelsField].as<JsonArray>();
        for (unsigned char i = 0; i < maxLevels; i++) {
          // break out at the first zero as this
          // will be the end of the levels
          if (levels[i] == 0) {
            return;
          }
          array.add(levels[i]);
        }
        object[saveStateDelayField] = saveStateDelay;
        object[offLevelField] = offLevel;
      }

      const BurpTree::Status & Factory::getStatus() const {
        return _status;
      }

      const BurpTree::State * Factory::deserialize(const JsonObject & object) {
        return _create([&](const Uid uid, void * address) {
          _status.set(Status::Level::INFO, Status::noError);
          if (!object.isNull()) {
            if (object.containsKey(levelsField)) {
              if (object.containsKey(saveStateDelayField)) {
                if (object.containsKey(offLevelField)) {
                  JsonArray array = object[levelsField].as<JsonArray>();
                  if (array) {
                    auto size = array.size();
                    if (size > maxLevels) {
                      return _fail(uid, address, Status::maxLevels);
                    }
                    if (size == 0) {
                      return _fail(uid, address, Status::minLevels);
                    }
                    auto index = 0;
                    State::Levels levels;
                    for(JsonVariant v : array) {
                      if (!v.is<State::Level>()) {
                        return _fail(uid, address, Status::invalidLevels);
                      }
                      const State::Level level = v.as<State::Level>();
                      if (level == 0) {
                        return _fail(uid, address, Status::levelZero);
                      }
                      levels[index++] = level;
                    }
                    if (!object[State::saveStateDelayField].is<State::Delay>()) {
                      return _fail(uid, address, Status::invalidSaveStateDelay);
                    }
                    State::Delay saveStateDelay = object[State::saveStateDelayField];
                    if (!object[State::offLevelField].is<State::Level>()) {
                      return _fail(uid, address, Status::invalidOffLevel);
                    }
                    State::Level offLevel = object[State::offLevelField];
                    if (offLevel >= size) {
                      return _fail(uid, address, Status::offLevelOutOfRange);
                    }
                    return new(address) State(uid, levels, saveStateDelay, offLevel);
                  }
                  return _fail(uid, address, Status::notAnArray);
                }
                return _fail(uid, address, Status::noOffLevel);
              }
              return _fail(uid, address, Status::noSaveStateDelay);
            }
            return _fail(uid, address, Status::noLevels);
          }
          return _fail(uid, address, Status::noObject);
        });
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
}
