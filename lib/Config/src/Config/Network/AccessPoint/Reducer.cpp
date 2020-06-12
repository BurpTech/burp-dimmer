#include "Reducer.hpp"

namespace Config {
  namespace Network {
    namespace AccessPoint {

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
          case ActionType::NETWORK_ACCESS_POINT_DESERIALIZE: {
            return alloc(
              previous,
              [&](void * address) {
                return new(address) State(
                  *(action.payload<JsonObject>())
                );
              }
            );
          }
          default:
            return previous;
        }
      }

    }
  }
}
