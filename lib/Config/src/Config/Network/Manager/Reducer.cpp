#include "./Reducer.hpp"
#include "./Actions.hpp"

namespace Config {
  namespace Network {
    namespace Manager {

      const Redux::State * Reducer::init(const Redux::State * state, const Redux::Reducer<State, ActionType, JsonObject>::f_withInit withInit) const {
        return withInit([&](const JsonObject * pObject) {
          return Redux::Reducer<State, ActionType, JsonObject>::_alloc(
            state->as<State>(),
            [&](void * address) {
              printf("init: %p\n", address);
              return new(address) State(*pObject);
            }
          );
        });
      }

      const Redux::State * Reducer::reduce(const Redux::State *state, const Redux::Action<ActionType> &action) const {
        switch (action.type) {
          case ActionType::NETWORK_MANAGER_DESERIALIZE: {
            return Redux::Reducer<State, ActionType, JsonObject>::_alloc(
              state->as<State>(),
              [&](void * address) {
                printf("deserialize: %p\n", address);
                return new(address) State(
                  action.as<Actions::Deserialize>().object
                );
              }
            );
          }
          case ActionType::NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT: {
            const State * manager = state->as<State>();
            printf("SetAccessPointTimeout: before->permMode: %d\n", manager->permMode);
            printf("SetAccessPointTimeout: before->tempMode: %d\n", manager->tempMode);
            printf("SetAccessPointTimeout: before->tempModeActive: %d\n", manager->tempModeActive);
            printf("SetAccessPointTimeout: before->accessPointTimeout: %u\n", manager->accessPointTimeout);
            return Redux::Reducer<State, ActionType, JsonObject>::_alloc(
              manager,
              [&](void * address) {
                printf("setAccessPointTimeout: %p\n", address);
                return new(address) State(
                  *manager,
                  action.as<Actions::SetAccessPointTimeout>().timeout
                );
              }
            );
          }
          case ActionType::NETWORK_MANAGER_NEXT_PERM_MODE: {
            return Redux::Reducer<State, ActionType, JsonObject>::_alloc(
              state->as<State>(),
              [&](void * address) {
                printf("nextPermMode: %p\n", address);
                return _createNextPermMode(
                  address,
                  *(state->as<State>())
                );
              }
            );
          }
          case ActionType::NETWORK_MANAGER_SET_PERM_MODE: {
            return Redux::Reducer<State, ActionType, JsonObject>::_alloc(
              state->as<State>(),
              [&](void * address) {
                printf("setPermMode: %p\n", address);
                return new(address) State(
                  *(state->as<State>()),
                  action.as<Actions::SetPermMode>().mode
                );
              }
            );
          }
          case ActionType::NETWORK_MANAGER_SET_TEMP_MODE: {
            return Redux::Reducer<State, ActionType, JsonObject>::_alloc(
              state->as<State>(),
              [&](void * address) {
                printf("setTempMode: %p\n", address);
                return new(address) State(
                  *(state->as<State>()),
                  action.as<Actions::SetTempMode>().mode
                );
              }
            );
          }
          default:
            return state;
        }
      }

      const State * Reducer::_createNextPermMode(void * address, const State & previous) {
        switch (previous.permMode) {
          case PermMode::NORMAL:
            return new(address) State(previous, PermMode::ACCESS_POINT);
          case PermMode::ACCESS_POINT:
            return new(address) State(previous, PermMode::OFF);
          case PermMode::OFF:
            return new(address) State(previous, PermMode::NORMAL);
        }
        return nullptr;
      }

    }
  }
}
