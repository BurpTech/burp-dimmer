#include "Serialization.hpp"
#include "Factory.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        constexpr PermMode defaultPermMode = PermMode::NORMAL;
        constexpr TempMode defaultTempMode = TempMode::ACCESS_POINT;
        constexpr bool defaultTempModeActive = false;
        constexpr Timeout defaultAccessPointTimeout = 0;

        bool Factory::deserialize(const JsonVariant & serialized) {
          return create([&]() -> const State * {
            Serialization serialization;
            auto code = serialization.deserialize(serialized);
            if (code == Status::ok) {
              return ok(new(getAddress()) State(
                static_cast<PermMode>(serialization.root.mode.value),
                defaultTempMode,
                defaultTempModeActive,
                serialization.root.accessPointTimeout.value
              ));
            }
            return error(code);
          });
        }

        bool Factory::nextPermMode() {
          return create([&]() -> const State * {
            const State * previous = getState();
            return ok(new(getAddress()) State(
                static_cast<PermMode>((previous->permMode + 1) % PermMode::count),
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
                TempMode::ACCESS_POINT,
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
                TempMode::WPS_CONFIG,
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
                PermMode::NORMAL,
                previous->tempMode,
                false,
                previous->accessPointTimeout
            ));
          });
        }

        bool Factory::createDefault() {
          return create([&]() -> const State * {
              return ok(new(getAddress()) State(
                defaultPermMode,
                defaultTempMode,
                defaultTempModeActive,
                defaultAccessPointTimeout
              ));
          });
        }

      }
    }
  }
}
