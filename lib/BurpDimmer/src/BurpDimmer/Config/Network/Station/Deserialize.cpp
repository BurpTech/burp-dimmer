#include <Util/Debug.hpp>
#include "Deserialize.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        void deserialize(const JsonObject & object, f_onState onState) {
          deserialize(object, [&](const Error error, const Params * params) {
              onState(memory.create(params));
          });
        }

        void deserialize(const JsonObject & object, f_onParams onParams) {
          if (!object.isNull()) {
            if (object.containsKey(testField)) {
              const JsonVariant v = object[testField];
              if (!v.is<int>()) {
                BURP_DEBUG_INFO("Error::invalidTest");
                return onParams(Error::invalidTest, nullptr);
              }
              const Params params = {
                v.as<int>()
              };
              return onParams(Error::noError, &params);
            }
            BURP_DEBUG_INFO("Error::noLevels");
            return onParams(Error::noTest, nullptr);
          }
          BURP_DEBUG_INFO("Error::noObject");
          return onParams(Error::noObject, nullptr);
        }

      }
    }
  }
}
