#include <Util/Debug.hpp>
#include "State.hpp"

namespace Config {
  namespace Light {

    constexpr char levelsField[] = "levels";
    constexpr unsigned char defaultLevelCount = 25;
    constexpr std::array<unsigned char, maxLevels>  defaultLevels = {
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

    State::State(const State * previous, const JsonObject & object) {
      lastError = Error::noError;
      if (!object.isNull()) {
        if (object.containsKey(levelsField)) {
          JsonArray array = object[levelsField].as<JsonArray>();
          if (array) {
            size_t size = array.size();
            if (size > maxLevels) {
              BURP_DEBUG_INFO("Error::maxLevels");
              lastError = Error::maxLevels;
            } else if (size == 0) {
              BURP_DEBUG_INFO("Error::minLevels");
              lastError = Error::minLevels;
            } else {
              levelCount = size;
              unsigned char count = 0;
              for(JsonVariant v : array) {
                if (v.is<unsigned char>()) {
                  levels[count++] = v.as<unsigned char>();
                } else {
                  BURP_DEBUG_INFO("Error::invalidLevels");
                  lastError = Error::invalidLevels;
                  break;
                }
              }
              if (lastError == Error::noError) {
                return;
              }
            }
          } else {
            BURP_DEBUG_INFO("Error::notAnArray");
            lastError = Error::notAnArray;
          }
        } else {
          BURP_DEBUG_INFO("Error::levelsNotProvided");
          lastError = Error::levelsNotProvided;
        }
      }
      if (previous) {
        BURP_DEBUG_INFO("Applying previous state");
        levelCount = previous->levelCount;
        levels = previous->levels;
      } else {
        BURP_DEBUG_INFO("Applying defaults");
        levelCount = defaultLevelCount;
        levels = defaultLevels;
      }
    }


    void State::serialize(JsonObject & object) const {
      JsonArray array = object[levelsField].as<JsonArray>();
      for (unsigned char i = 0; i < levelCount; i++) {
        array.add(levels[i]);
      }
    }

  }
}
