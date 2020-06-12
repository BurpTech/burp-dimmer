#include "Reducer.hpp"

namespace Config {
  namespace Light {

    const State * Reducer::init(const State * previous, const JsonObject & object) const {
      return alloc(
        previous,
        [&](void * address) {
          return new(address) State(previous, object);
        }
      );
    }

    const State * Reducer::reduce(const State * previous, const Action & action) const {
      switch (action.type) {
        case ActionType::LIGHT_DESERIALIZE: {
          return alloc(
            previous,
            [&](void * address) {
              return new(address) State(
                previous,
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
