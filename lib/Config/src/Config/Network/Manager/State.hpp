#pragma once

#include <ArduinoJson.h>
#include <Json/Serializer.hpp>
#include <Redux/State.hpp>

namespace Config {
  namespace Network {
    namespace Manager {

      enum class PermMode {
        NORMAL,
        ACCESS_POINT,
        OFF
      };

      enum class TempMode {
        ACCESS_POINT,
        WPS_CONFIG
      };

      class State : public Json::Serializer, public Redux::State {
        public:

          static constexpr char MODE_FIELD[] = "mode";
          static constexpr char ACCESS_POINT_TIMEOUT_FIELD[] = "accessPointTimeout";
          static constexpr PermMode DEFAULT_PERM_MODE = PermMode::NORMAL;
          static constexpr TempMode DEFAULT_TEMP_MODE = TempMode::ACCESS_POINT;
          static constexpr bool DEFAULT_TEMP_MODE_ACTIVE = false;
          static constexpr unsigned long DEFAULT_ACCESS_POINT_TIMEOUT = 0;

          const PermMode permMode;
          const TempMode tempMode;
          const bool tempModeActive;
          const unsigned long accessPointTimeout;

          State(const State & state, const unsigned long timeout);
          State(const State & state, PermMode mode);
          State(const State & state, TempMode mode);
          State(const JsonObject & object);
          void serialize(JsonObject & object) const override;

      };

    }
  }
}
