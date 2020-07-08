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
          const Levels levels,
          const Delay saveStateDelay,
          const Level offLevel
      ) :
        levels(levels),
        saveStateDelay(saveStateDelay),
        offLevel(offLevel)
      {}

      State::State() :
        State(defaultLevels, defaultSaveStateDelay, defaultOffLevel)
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

      bool Factory::deserialize(const JsonObject & object) {
        return create([&]() -> const State * {
          if (!object.isNull()) {
            if (object.containsKey(levelsField)) {
              if (object.containsKey(saveStateDelayField)) {
                if (object.containsKey(offLevelField)) {
                  JsonArray array = object[levelsField].as<JsonArray>();
                  if (array) {
                    auto size = array.size();
                    if (size > maxLevels) {
                      return error(Status::maxLevels);
                    }
                    if (size == 0) {
                      return error(Status::minLevels);
                    }
                    auto index = 0;
                    State::Levels levels;
                    for(JsonVariant v : array) {
                      if (!v.is<State::Level>()) {
                        return error(Status::invalidLevels);
                      }
                      const State::Level level = v.as<State::Level>();
                      if (level == 0) {
                        return error(Status::levelZero);
                      }
                      levels[index++] = level;
                    }
                    if (!object[saveStateDelayField].is<State::Delay>()) {
                      return error(Status::invalidSaveStateDelay);
                    }
                    State::Delay saveStateDelay = object[saveStateDelayField];
                    if (!object[offLevelField].is<State::Level>()) {
                      return error(Status::invalidOffLevel);
                    }
                    State::Level offLevel = object[offLevelField];
                    if (offLevel >= size) {
                      return error(Status::offLevelOutOfRange);
                    }
                    return ok(new(getAddress()) State(levels, saveStateDelay, offLevel));
                  }
                  return error(Status::notAnArray);
                }
                return error(Status::noOffLevel);
              }
              return error(Status::noSaveStateDelay);
            }
            return error(Status::noLevels);
          }
          return error(Status::noObject);
        });
      }

      bool Factory::createDefault() {
        return create([&]() -> const State * {
            return ok(new(getAddress()) State());
        });
      }

      #define C_STR_LABEL "BurpDimmer::Config::Light"
      #define C_STR_CASE(CODE) BURP_STATUS_C_STR_CASE(C_STR_LABEL, CODE)
      #define C_STR_DEFAULT BURP_STATUS_C_STR_DEFAULT(C_STR_LABEL)
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
