#include "./Reducer.hpp"
#include "./Actions.hpp"
#include "ArduinoJson.hpp"

namespace Config {
  namespace Network {
    namespace Manager {

      const State * Reducer::init(const State * previous, const JsonObject & object) const {
        return alloc(
          previous,
          [&](void * address) {
            return new(address) State(object);
          }
        );
      }

      const State * Reducer::reduce(const State *previous, const Redux::Action<ActionType> &action) const {
        switch (action.type) {
          case ActionType::NETWORK_MANAGER_DESERIALIZE: {
            return alloc(
              previous,
              [&](void * address) {
                return new(address) State(
                  action.as<Actions::Deserialize>().object
                );
              }
            );
          }
          case ActionType::NETWORK_MANAGER_SET_ACCESS_POINT_TIMEOUT: {
            return alloc(
              previous,
              [&](void * address) {
                return new(address) State(
                  *previous,
                  action.as<Actions::SetAccessPointTimeout>().timeout
                );
              }
            );
          }
          case ActionType::NETWORK_MANAGER_NEXT_PERM_MODE: {
            return alloc(
              previous,
              [&](void * address) {
                return _createNextPermMode(
                  address,
                  *previous
                );
              }
            );
          }
          case ActionType::NETWORK_MANAGER_SET_PERM_MODE: {
            return alloc(
              previous,
              [&](void * address) {
                return new(address) State(
                  *previous,
                  action.as<Actions::SetPermMode>().mode
                );
              }
            );
          }
          case ActionType::NETWORK_MANAGER_SET_TEMP_MODE: {
            return alloc(
              previous,
              [&](void * address) {
                return new(address) State(
                  *previous,
                  action.as<Actions::SetTempMode>().mode
                );
              }
            );
          }
          default:
            return previous;
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
