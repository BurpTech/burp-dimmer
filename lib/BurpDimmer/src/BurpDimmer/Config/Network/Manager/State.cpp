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
            const Uid uid,
            const PermMode permMode,
            const TempMode tempMode,
            const bool tempModeActive,
            const Timeout accessPointTimeout
        ) :
          BurpTree::State(uid),
          permMode(permMode),
          tempMode(tempMode),
          tempModeActive(tempModeActive),
          accessPointTimeout(accessPointTimeout)
        {}

        State::State(const Uid uid) :
          State(
              uid,
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

        const BurpTree::State * Factory::deserialize(const JsonObject & object) {
          return create([&]() -> const State * {
            if (!object.isNull()) {
              if (object.containsKey(modeField)) {
                if (object.containsKey(accessPointTimeoutField)) {
                  const JsonVariant vapt = object[accessPointTimeoutField];
                  if (!vapt.is<State::Timeout>()) {
                    return fail(Status::invalidAccessPointTimeout);
                  }
                  const State::Timeout accessPointTimeout = vapt.as<State::Timeout>();
                  const JsonVariant vm = object[modeField];
                  if (!vm.is<const char *>()) {
                    return fail(Status::invalidMode);
                  }
                  const char * modeString = vm.as<const char *>();
                  for (size_t i = 0 ; i < State::PermMode::count; i++) {
                    if (strcmp(modeString, permModeNames[i]) == 0) {
                      return new(getAddress()) State(
                          getUid(),
                          static_cast<State::PermMode>(i),
                          defaultTempMode,
                          defaultTempModeActive,
                          accessPointTimeout
                      );
                    }
                  }
                  return fail(Status::unknownMode);
                }
                return fail(Status::noAccessPointTimeout);
              }
              return fail(Status::noMode);
            }
            return fail(Status::noObject);
          });
        }

        const BurpTree::State * Factory::nextPermMode() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return new(getAddress()) State(
                getUid(),
                static_cast<State::PermMode>((previous->permMode + 1) % State::PermMode::count),
                previous->tempMode,
                previous->tempModeActive,
                previous->accessPointTimeout
            );
          });
        }

        const BurpTree::State * Factory::startTempAccessPoint() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return new(getAddress()) State(
                getUid(),
                previous->permMode,
                State::TempMode::ACCESS_POINT,
                true,
                previous->accessPointTimeout
            );
          });
        }

        const BurpTree::State * Factory::startWpsConfig() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return new(getAddress()) State(
                getUid(),
                previous->permMode,
                State::TempMode::WPS_CONFIG,
                true,
                previous->accessPointTimeout
            );
          });
        }

        const BurpTree::State * Factory::stopTempMode() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return new(getAddress()) State(
                getUid(),
                previous->permMode,
                previous->tempMode,
                false,
                previous->accessPointTimeout
            );
          });
        }

        const BurpTree::State * Factory::setNormalMode() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return new(getAddress()) State(
                getUid(),
                State::PermMode::NORMAL,
                previous->tempMode,
                false,
                previous->accessPointTimeout
            );
          });
        }

        const State * Factory::_default() {
          return new(getAddress()) State(getUid());
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
