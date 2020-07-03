#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        constexpr char modeField[] = "mode";
        constexpr char accessPointTimeoutField[] = "accessPointTimeout";

        constexpr State::PermMode defaultPermMode = State::PermMode::NORMAL;
        constexpr State::TempMode defaultTempMode = State::TempMode::ACCESS_POINT;
        constexpr bool defaultTempModeActive = false;
        constexpr State::Timeout defaultAccessPointTimeout = 0;

        constexpr std::array<const char *, State::PermMode::count> permModeNames = {
          "normal",
          "accessPoint",
          "off"
        };

        State::State(
            const PermMode permMode,
            const TempMode tempMode,
            const bool tempModeActive,
            const Timeout accessPointTimeout
        ) :
          permMode(permMode),
          tempMode(tempMode),
          tempModeActive(tempModeActive),
          accessPointTimeout(accessPointTimeout)
        {}

        State::State() :
          State(
              defaultPermMode,
              defaultTempMode,
              defaultTempModeActive,
              defaultAccessPointTimeout
          )
        {}

        void State::serialize(const JsonObject & object) const {
          // don't serialize the tempMode as it should not be restored
          object[modeField] = permModeNames[permMode];
          object[accessPointTimeoutField] = accessPointTimeout;
        }

        bool Factory::deserialize(const JsonObject & object) {
          return create([&]() -> const State * {
            if (!object.isNull()) {
              if (object.containsKey(modeField)) {
                if (object.containsKey(accessPointTimeoutField)) {
                  const JsonVariant vapt = object[accessPointTimeoutField];
                  if (!vapt.is<State::Timeout>()) {
                    return error(Status::invalidAccessPointTimeout);
                  }
                  const State::Timeout accessPointTimeout = vapt.as<State::Timeout>();
                  const JsonVariant vm = object[modeField];
                  if (!vm.is<const char *>()) {
                    return error(Status::invalidMode);
                  }
                  const char * modeString = vm.as<const char *>();
                  for (size_t i = 0 ; i < State::PermMode::count; i++) {
                    if (strcmp(modeString, permModeNames[i]) == 0) {
                      return ok(new(getAddress()) State(
                          static_cast<State::PermMode>(i),
                          defaultTempMode,
                          defaultTempModeActive,
                          accessPointTimeout
                      ));
                    }
                  }
                  return error(Status::unknownMode);
                }
                return error(Status::noAccessPointTimeout);
              }
              return error(Status::noMode);
            }
            return error(Status::noObject);
          });
        }

        bool Factory::nextPermMode() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return ok(new(getAddress()) State(
                static_cast<State::PermMode>((previous->permMode + 1) % State::PermMode::count),
                previous->tempMode,
                previous->tempModeActive,
                previous->accessPointTimeout
            ));
          });
        }

        bool Factory::startTempAccessPoint() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return ok(new(getAddress()) State(
                previous->permMode,
                State::TempMode::ACCESS_POINT,
                true,
                previous->accessPointTimeout
            ));
          });
        }

        bool Factory::startWpsConfig() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return ok(new(getAddress()) State(
                previous->permMode,
                State::TempMode::WPS_CONFIG,
                true,
                previous->accessPointTimeout
            ));
          });
        }

        bool Factory::stopTempMode() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return ok(new(getAddress()) State(
                previous->permMode,
                previous->tempMode,
                false,
                previous->accessPointTimeout
            ));
          });
        }

        bool Factory::setNormalMode() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return ok(new(getAddress()) State(
                State::PermMode::NORMAL,
                previous->tempMode,
                false,
                previous->accessPointTimeout
            ));
          });
        }

        bool Factory::createDefault() {
          return create([&]() -> const State * {
              return ok(new(getAddress()) State());
          });
        }

        #define C_STR_LABEL "BurpDimmer::Config::Network::Manager"
        #define C_STR_CASE(CODE) BURP_TREE_C_STR_CASE(C_STR_LABEL, CODE)
        #define C_STR_DEFAULT BURP_TREE_C_STR_DEFAULT(C_STR_LABEL)
        const char * Status::c_str() const {
          switch (getCode()) {
            C_STR_CASE(ok);
            C_STR_CASE(noObject);
            C_STR_CASE(noMode);
            C_STR_CASE(noAccessPointTimeout);
            C_STR_CASE(invalidMode);
            C_STR_CASE(invalidAccessPointTimeout);
            C_STR_CASE(unknownMode);
            C_STR_DEFAULT;
          }
        }

      }
    }
  }
}
