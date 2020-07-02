#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      constexpr char levelsField[] = "levels";
      constexpr char saveStateDelayField[] = "saveStateDelay";
      constexpr char offLevelField[] = "offLevelField";

      constexpr State::Levels defaultLevels = {
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

      const BurpTree::State * Factory::deserialize(const JsonObject & object) {
        return create([&]() -> const State * {
          if (!object.isNull()) {
            if (object.containsKey(levelsField)) {
              if (object.containsKey(saveStateDelayField)) {
                if (object.containsKey(offLevelField)) {
                  JsonArray array = object[levelsField].as<JsonArray>();
                  if (array) {
                    auto size = array.size();
                    if (size > maxLevels) {
                      return fail(Status::maxLevels);
                    }
                    if (size == 0) {
                      return fail(Status::minLevels);
                    }
                    auto index = 0;
                    State::Levels levels;
                    for(JsonVariant v : array) {
                      if (!v.is<State::Level>()) {
                        return fail(Status::invalidLevels);
                      }
                      const State::Level level = v.as<State::Level>();
                      if (level == 0) {
                        return fail(Status::levelZero);
                      }
                      levels[index++] = level;
                    }
                    if (!object[saveStateDelayField].is<State::Delay>()) {
                      return fail(Status::invalidSaveStateDelay);
                    }
                    State::Delay saveStateDelay = object[saveStateDelayField];
                    if (!object[offLevelField].is<State::Level>()) {
                      return fail(Status::invalidOffLevel);
                    }
                    State::Level offLevel = object[offLevelField];
                    if (offLevel >= size) {
                      return fail(Status::offLevelOutOfRange);
                    }
                    return new(getAddress()) State(getUid(), levels, saveStateDelay, offLevel);
                  }
                  return fail(Status::notAnArray);
                }
                return fail(Status::noOffLevel);
              }
              return fail(Status::noSaveStateDelay);
            }
            return fail(Status::noLevels);
          }
          return fail(Status::noObject);
        });
      }

      const State * Factory::_default() {
        return new(getAddress()) State(getUid());
      }

      #define C_STR_LABEL "BurpDimmer::Config::Light"
      #define C_STR_CASE(CODE) BURP_TREE_C_STR_CASE(C_STR_LABEL, CODE)
      #define C_STR_DEFAULT BURP_TREE_C_STR_DEFAULT(C_STR_LABEL)
      const char * Status::c_str() const {
        switch (getCode()) {
          C_STR_CASE(ok);
          C_STR_CASE(noObject);
          C_STR_CASE(noLevels);
          C_STR_CASE(noSaveStateDelay);
          C_STR_CASE(noOffLevel);
          C_STR_CASE(notAnArray);
          C_STR_CASE(minLevels);
          C_STR_CASE(maxLevels);
          C_STR_CASE(invalidLevels);
          C_STR_CASE(invalidSaveStateDelay);
          C_STR_CASE(invalidOffLevel);
          C_STR_CASE(offLevelOutOfRange);
          C_STR_CASE(levelZero);
          C_STR_DEFAULT;
        }
      }

    }
  }
}
