#include <BurpDebug.hpp>
#include "Actions.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        void deserialize(const JsonObject & object, State::Params & params) {
          params.error = State::Error::noError;
          if (!object.isNull()) {
            if (object.containsKey(State::testField)) {
              const JsonVariant v = object[State::testField];
              if (!v.is<int>()) {
                BURP_DEBUG_INFO("Error::invalidTest");
                params.error = State::Error::invalidTest;
                return;
              }
              params.test = v.as<int>();
              return;
            }
            BURP_DEBUG_INFO("Error::noTest");
            params.error = State::Error::noTest;
            return;
          }
          BURP_DEBUG_INFO("Error::noObject");
          params.error = State::Error::noObject;
        }

      }
    }
  }
}
