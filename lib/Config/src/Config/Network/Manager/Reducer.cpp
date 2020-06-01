#include "./Reducer.hpp"
#include "./Actions.hpp"

namespace Config {
  namespace Network {
    namespace Manager {

      void Reducer::deserialize(const JsonObject & object) {
        _initialState = new State(object);
      }

      const Redux::State * Reducer::init() const {
        return _initialState;
      }

      const Redux::State * Reducer::reduce(const Redux::State *state, const Redux::Action<ActionType> &action) const {
        switch (action.type) {
          case ActionType::NETWORK_MANAGER_DESERIALIZE: {
            return Redux::State::replace(state, new State(
              action.as<Actions::Deserialize>().object
            ));
          }
          case ActionType::NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT: {
            return Redux::State::replace(state, new State(
              *(state->as<State>()),
              action.as<Actions::SetAccessPointTimeout>().timeout
            ));
          }
          case ActionType::NETWORK_MANAGER_NEXT_PERM_MODE: {
            return Redux::State::replace(state, _createNextPermMode(
              *(state->as<State>())
            ));
          }
          case ActionType::NETWORK_MANAGER_SET_PERM_MODE: {
            return Redux::State::replace(state, new State(
              *(state->as<State>()),
              action.as<Actions::SetPermMode>().mode
            ));
          }
          case ActionType::NETWORK_MANAGER_SET_TEMP_MODE: {
            return Redux::State::replace(state, new State(
              *(state->as<State>()),
              action.as<Actions::SetTempMode>().mode
            ));
          }
          default:
            return state;
        }
      }

      const State * Reducer::_createNextPermMode(const State & previous) {
        switch (previous.permMode) {
          case PermMode::NORMAL:
            return new State(previous, PermMode::ACCESS_POINT);
          case PermMode::ACCESS_POINT:
            return new State(previous, PermMode::OFF);
          case PermMode::OFF:
            return new State(previous, PermMode::NORMAL);
        }
        return nullptr;
      }

    }
  }
}
