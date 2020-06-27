#include <BurpDebug.hpp>
#include "Actions.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        void deserialize(const JsonObject & object, State::Params & params) {
          params.error = State::Error::noError;
          if (!object.isNull()) {
            if (object.containsKey(State::modeField)) {
              if (object.containsKey(State::accessPointTimeoutField)) {
                const JsonVariant vapt = object[State::accessPointTimeoutField];
                if (!vapt.is<unsigned long>()) {
                  BURP_DEBUG_INFO("Error::invalidAccessPointTimeout");
                  params.error = State::Error::invalidAccessPointTimeout;
                  return;
                }
                const unsigned long accessPointTimeout = vapt.as<unsigned long>();
                const JsonVariant vm = object[State::modeField];
                if (!vm.is<const char *>()) {
                  BURP_DEBUG_INFO("Error::invalidMode");
                  params.error = State::Error::invalidMode;
                  return;
                }
                const char * modeString = vm.as<const char *>();
                for (size_t i = 0 ; i < State::PermMode::count; i++) {
                  if (strcmp(modeString, State::permModeNames[i]) == 0) {
                    params.permMode = static_cast<State::PermMode>(i);
                    params.tempMode = State::defaultTempMode;
                    params.tempModeActive = State::defaultTempModeActive;
                    params.accessPointTimeout = accessPointTimeout;
                    return;
                  }
                }
                BURP_DEBUG_INFO("Error::unknownMode");
                params.error = State::Error::unknownMode;
                return;
              }
              BURP_DEBUG_INFO("Error::noAccessPointTimeout");
              params.error = State::Error::noAccessPointTimeout;
              return;
            }
            BURP_DEBUG_INFO("Error::noMode");
            params.error = State::Error::noMode;
            return;
          }
          BURP_DEBUG_INFO("Error::noObject");
          params.error = State::Error::noObject;
        }

        void nextPermMode(const State::Instance * previous, State::Params & params) {
          params.error = State::Error::noError;
          params.permMode = static_cast<State::PermMode>((previous->permMode + 1) % State::PermMode::count);
          params.tempMode = previous->tempMode;
          params.tempModeActive = false;
          params.accessPointTimeout = previous->accessPointTimeout;
        }

        void startTempAccessPoint(const State::Instance * previous, State::Params & params) {
          params.error = State::Error::noError;
          params.permMode = previous->permMode;
          params.tempMode = State::TempMode::ACCESS_POINT;
          params.tempModeActive = true;
          params.accessPointTimeout = previous->accessPointTimeout;
        }

        void startWpsConfig(const State::Instance * previous, State::Params & params) {
          params.error = State::Error::noError;
          params.permMode = previous->permMode;
          params.tempMode = State::TempMode::WPS_CONFIG;
          params.tempModeActive = true;
          params.accessPointTimeout = previous->accessPointTimeout;
        }

        void stopTempMode(const State::Instance * previous, State::Params & params) {
          params.error = State::Error::noError;
          params.permMode = previous->permMode;
          params.tempMode = previous->tempMode;
          params.tempModeActive = false;
          params.accessPointTimeout = previous->accessPointTimeout;
        }

        void setNormalMode(const State::Instance * previous, State::Params & params) {
          params.error = State::Error::noError;
          params.permMode = State::PermMode::NORMAL;
          params.tempMode = previous->tempMode;
          params.tempModeActive = false;
          params.accessPointTimeout = previous->accessPointTimeout;
        }

      }
    }
  }
}
