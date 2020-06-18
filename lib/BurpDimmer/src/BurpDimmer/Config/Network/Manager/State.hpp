#pragma once

#include <array>
#include <Json/Serializer.hpp>
#include <Memory/Pair.hpp>
#include <cstddef>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        constexpr char modeField[] = "mode";
        constexpr char accessPointTimeoutField[] = "accessPointTimeout";

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
          const PermMode permMode;
          const TempMode tempMode;
          const bool tempModeActive;
          const unsigned long accessPointTimeout;
        };

        class State : public Json::Serializer {

          public:
            
            const PermMode permMode;
            const TempMode tempMode;
            const bool tempModeActive;
            const unsigned long accessPointTimeout;

            State(const Params * params);
            void serialize(JsonObject & object) const override;

        };

        extern Memory::Pair<State, Params> memory;

      }
    }
  }
}
