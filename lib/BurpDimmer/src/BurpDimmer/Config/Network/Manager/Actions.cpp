#include "../../../Util/Debug.hpp"
#include "Actions.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        void deserialize(const JsonObject & object, f_onParams onParams) {
          if (!object.isNull()) {
            if (object.containsKey(State::modeField)) {
              if (object.containsKey(State::accessPointTimeoutField)) {
                const JsonVariant vapt = object[State::accessPointTimeoutField];
                if (!vapt.is<unsigned long>()) {
                  BURP_DEBUG_INFO("Error::invalidAccessPointTimeout");
                  return onParams(Error::invalidAccessPointTimeout, nullptr);
                }
                const unsigned long accessPointTimeout = vapt.as<unsigned long>();
                const JsonVariant vm = object[State::modeField];
                if (!vm.is<const char *>()) {
                  BURP_DEBUG_INFO("Error::invalidMode");
                  return onParams(Error::invalidMode, nullptr);
                }
                const char * modeString = vm.as<const char *>();
                for (size_t i = 0 ; i < State::PermMode::count; i++) {
                  if (strcmp(modeString, State::permModeNames[i]) == 0) {
                    const State::Params params = {
                      static_cast<State::PermMode>(i),
                      State::defaultTempMode,
                      State::defaultTempModeActive,
                      accessPointTimeout
                    };
                    return onParams(Error::noError, &params);
                  }
                }
                BURP_DEBUG_INFO("Error::unknownMode");
                return onParams(Error::unknownMode, nullptr);
              }
              BURP_DEBUG_INFO("Error::noAccessPointTimeout");
              return onParams(Error::noAccessPointTimeout, nullptr);
            }
            BURP_DEBUG_INFO("Error::noMode");
            return onParams(Error::noMode, nullptr);
          }
          BURP_DEBUG_INFO("Error::noObject");
          return onParams(Error::noObject, nullptr);
        }

        void nextPermMode(const State::Instance * previous, f_onParams onParams) {
          const State::Params params = {
            static_cast<State::PermMode>((previous->permMode + 1) % State::PermMode::count),
            previous->tempMode,
            false,
            previous->accessPointTimeout
          };
          return onParams(Error::noError, &params);
        }

        void startTempAccessPoint(const State::Instance * previous, f_onParams onParams) {
          const State::Params params = {
            previous->permMode,
            State::TempMode::ACCESS_POINT,
            true,
            previous->accessPointTimeout
          };
          return onParams(Error::noError, &params);
        }

        void startWpsConfig(const State::Instance * previous, f_onParams onParams) {
          const State::Params params = {
            previous->permMode,
            State::TempMode::WPS_CONFIG,
            true,
            previous->accessPointTimeout
          };
          return onParams(Error::noError, &params);
        }

        void stopTempMode(const State::Instance * previous, f_onParams onParams) {
          const State::Params params = {
            previous->permMode,
            previous->tempMode,
            false,
            previous->accessPointTimeout
          };
          return onParams(Error::noError, &params);
        }

        void setNormalMode(const State::Instance * previous, f_onParams onParams) {
          const State::Params params = {
            State::PermMode::NORMAL,
            previous->tempMode,
            false,
            previous->accessPointTimeout
          };
          return onParams(Error::noError, &params);
        }

      }
    }
  }
}
