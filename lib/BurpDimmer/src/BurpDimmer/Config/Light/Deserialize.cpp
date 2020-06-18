#include <Util/Debug.hpp>
#include "Deserialize.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      void deserialize(const JsonObject & object, f_onState onState) {
        deserialize(object, [&](const Error error, const Levels * levels) {
            onState(memory.create(levels));
        });
      }

      void deserialize(const JsonObject & object, f_onLevels onLevels) {
        if (!object.isNull()) {
          if (object.containsKey(levelsField)) {
            JsonArray array = object[levelsField].as<JsonArray>();
            if (array) {
              auto size = array.size();
              if (size > maxLevels) {
                BURP_DEBUG_INFO("Error::maxLevels");
                return onLevels(Error::maxLevels, nullptr);
              }
              if (size == 0) {
                BURP_DEBUG_INFO("Error::minLevels");
                return onLevels(Error::minLevels, nullptr);
              }
              auto levelCount = size;
              auto index = 0;
              Levels levels;
              for(JsonVariant v : array) {
                if (!v.is<unsigned char>()) {
                  BURP_DEBUG_INFO("Error::invalidLevels");
                  return onLevels(Error::invalidLevels, nullptr);
                }
                const unsigned char level = v.as<unsigned char>();
                if (level == 0) {
                  BURP_DEBUG_INFO("Error::levelZero");
                  return onLevels(Error::levelZero, nullptr);
                }
                levels[index++] = level;
              }
              return onLevels(Error::noError, &levels);
            }
            BURP_DEBUG_INFO("Error::notAnArray");
            return onLevels(Error::notAnArray, nullptr);
          }
          BURP_DEBUG_INFO("Error::noLevels");
          return onLevels(Error::noLevels, nullptr);
        }
        BURP_DEBUG_INFO("Error::noObject");
        return onLevels(Error::noObject, nullptr);
      }

    }
  }
}
