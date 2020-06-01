#include "./State.hpp"

namespace Config {
  namespace Network {
    namespace Manager {

      constexpr char State::MODE_FIELD[];
      constexpr char State::ACCESS_POINT_TIMEOUT_FIELD[];
      constexpr PermMode State::DEFAULT_PERM_MODE;
      constexpr TempMode State::DEFAULT_TEMP_MODE;
      constexpr bool State::DEFAULT_TEMP_MODE_ACTIVE;
      constexpr unsigned long State::DEFAULT_ACCESS_POINT_TIMEOUT;


      State::State(const State & state, const unsigned long timeout) :
        permMode(state.permMode),
        tempMode(state.tempMode),
        tempModeActive(state.tempModeActive),
        accessPointTimeout(timeout) {
      }

      State::State(const State & state, PermMode mode) :
        permMode(mode),
        tempMode(DEFAULT_TEMP_MODE),
        tempModeActive(false),
        accessPointTimeout(state.accessPointTimeout) {
      }

      State::State(const State & state, TempMode mode) :
        permMode(state.permMode),
        tempMode(mode),
        tempModeActive(true),
        accessPointTimeout(state.accessPointTimeout) {
      }

      State::State(const JsonObject & object) :
        permMode(static_cast<PermMode>(object[State::MODE_FIELD].as<int>())),
        tempMode(DEFAULT_TEMP_MODE),
        tempModeActive(DEFAULT_TEMP_MODE_ACTIVE),
        accessPointTimeout(object[State::ACCESS_POINT_TIMEOUT_FIELD].as<unsigned long>()) {
      }

      void State::serialize(JsonObject & object) const {
        // don't serialize the tempMode as it should not be restored
        object[State::MODE_FIELD] = static_cast<int>(permMode);
        object[State::ACCESS_POINT_TIMEOUT_FIELD] = accessPointTimeout;
      }

    }
  }
}
