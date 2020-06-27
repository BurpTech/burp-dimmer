#include <BurpDebug.hpp>
#include "Actions.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      void deserialize(const JsonObject & object, State::Params & params) {
        params.error = State::Error::noError;
        if (!object.isNull()) {
          if (object.containsKey(State::levelsField)) {
            if (object.containsKey(State::saveStateDelayField)) {
              if (object.containsKey(State::offLevelField)) {
                JsonArray array = object[State::levelsField].as<JsonArray>();
                if (array) {
                  auto size = array.size();
                  if (size > State::maxLevels) {
                    BURP_DEBUG_INFO("Error::maxLevels");
                    params.error = State::Error::maxLevels;
                    return;
                  }
                  if (size == 0) {
                    BURP_DEBUG_INFO("Error::minLevels");
                    params.error = State::Error::minLevels;
                    return;
                  }
                  auto index = 0;
                  State::Levels levels;
                  for(JsonVariant v : array) {
                    if (!v.is<unsigned char>()) {
                      BURP_DEBUG_INFO("Error::invalidLevels");
                      params.error = State::Error::invalidLevels;
                      return;
                    }
                    const unsigned char level = v.as<unsigned char>();
                    if (level == 0) {
                      BURP_DEBUG_INFO("Error::levelZero");
                      params.error = State::Error::levelZero;
                      return;
                    }
                    levels[index++] = level;
                  }
                  if (!object[State::saveStateDelayField].is<unsigned long>()) {
                    BURP_DEBUG_INFO("Error::invalidSaveStateDelay");
                    params.error = State::Error::invalidSaveStateDelay;
                    return;
                  }
                  unsigned long saveStateDelay = object[State::saveStateDelayField];
                  if (!object[State::offLevelField].is<unsigned char>()) {
                    BURP_DEBUG_INFO("Error::invalidOffLevel");
                    params.error = State::Error::invalidOffLevel;
                    return;
                  }
                  unsigned char offLevel = object[State::offLevelField];
                  if (offLevel >= size) {
                    BURP_DEBUG_INFO("Error::offLevelOutOfRange");
                    params.error = State::Error::offLevelOutOfRange;
                    return;
                  }
                  params.levels = levels;
                  params.saveStateDelay = saveStateDelay;
                  params.offLevel = offLevel;
                  return;
                }
                BURP_DEBUG_INFO("Error::notAnArray");
                params.error = State::Error::notAnArray;
                return;
              }
              BURP_DEBUG_INFO("Error::noOffLevel");
              params.error = State::Error::noOffLevel;
              return;
            }
            BURP_DEBUG_INFO("Error::noSaveStateDelay");
            params.error = State::Error::noSaveStateDelay;
            return;
          }
          BURP_DEBUG_INFO("Error::noLevels");
          params.error = State::Error::noLevels;
          return;
        }
        BURP_DEBUG_INFO("Error::noObject");
        params.error = State::Error::noObject;
      }

    }
  }
}
