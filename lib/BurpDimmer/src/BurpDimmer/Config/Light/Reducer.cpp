#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      const Reducer reducer;

      const State * Reducer::reduce(const State * previous, const Action & action) const {
        switch (action.type) {
          case ActionType::LIGHT_SET_STATE: {
            return memory.create(action.payload<Levels>());
          }
          default:
            return previous;
        }
      }

    }
  }
}
