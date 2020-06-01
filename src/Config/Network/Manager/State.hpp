#pragma once

#include <ArduinoJson.h>
#include "../../../Util/Debug.hpp"
#include "../../../Json/Serializer.hpp"
#include "../../../Redux/State.hpp"

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

          State(const State & state, const unsigned long timeout) :
            permMode(state.permMode),
            tempMode(state.tempMode),
            tempModeActive(state.tempModeActive),
            accessPointTimeout(timeout) {
          }

          State(const State & state, PermMode mode) :
            permMode(mode),
            tempMode(DEFAULT_TEMP_MODE),
            tempModeActive(false),
            accessPointTimeout(state.accessPointTimeout) {
          }

          State(const State & state, TempMode mode) :
            permMode(state.permMode),
            tempMode(mode),
            tempModeActive(true),
            accessPointTimeout(state.accessPointTimeout) {
          }

          State(const JsonObject & object) :
            permMode(static_cast<PermMode>(object[State::MODE_FIELD].as<int>())),
            tempMode(DEFAULT_TEMP_MODE),
            tempModeActive(DEFAULT_TEMP_MODE_ACTIVE),
            accessPointTimeout(object[State::ACCESS_POINT_TIMEOUT_FIELD].as<unsigned long>()) {
          }

          void serialize(JsonObject & object) const override {
            // don't serialize the tempMode as it should not be restored
            object[State::MODE_FIELD] = static_cast<int>(permMode);
            object[State::ACCESS_POINT_TIMEOUT_FIELD] = accessPointTimeout;
          }

      };

      constexpr char State::MODE_FIELD[];
      constexpr char State::ACCESS_POINT_TIMEOUT_FIELD[];
      constexpr PermMode State::DEFAULT_PERM_MODE;
      constexpr TempMode State::DEFAULT_TEMP_MODE;
      constexpr bool State::DEFAULT_TEMP_MODE_ACTIVE;
      constexpr unsigned long State::DEFAULT_ACCESS_POINT_TIMEOUT;

    }
  }
}
