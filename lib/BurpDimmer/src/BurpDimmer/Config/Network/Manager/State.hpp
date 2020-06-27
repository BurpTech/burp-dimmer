#pragma once

#include <array>
#include <cstddef>
#include <ArduinoJson.h>
#include <BurpRedux/State/Instance.hpp>
#include <BurpRedux/Creator/Instance.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {
        namespace State {

          constexpr char modeField[] = "mode";
          constexpr char accessPointTimeoutField[] = "accessPointTimeout";

          enum class Error {
            noError,
            noObject,
            noMode,
            noAccessPointTimeout,
            invalidMode,
            invalidAccessPointTimeout,
            unknownMode
          };

          enum PermMode : size_t {
            NORMAL = 0,
            ACCESS_POINT,
            OFF,
            count
          };

          constexpr std::array<const char *, PermMode::count> permModeNames = {
            "normal",
            "accessPoint",
            "off"
          };

          enum class TempMode {
            ACCESS_POINT,
            WPS_CONFIG
          };

          constexpr TempMode defaultTempMode = TempMode::ACCESS_POINT;
          constexpr bool defaultTempModeActive = false;

          struct Params {
            Error error;
            PermMode permMode;
            TempMode tempMode;
            bool tempModeActive;
            unsigned long accessPointTimeout;
          };

          class Instance : public BurpRedux::State::Instance {

            public:
              
              const PermMode permMode;
              const TempMode tempMode;
              const bool tempModeActive;
              const unsigned long accessPointTimeout;

              Instance(const Params & params, const unsigned long uid);
              void serialize(const JsonObject & object) const override;

          };

          using Creator = BurpRedux::Creator::Instance<Instance, Params>;

        }
      }
    }
  }
}
