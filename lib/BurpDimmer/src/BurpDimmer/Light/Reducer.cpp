#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Light {

    const Reducer reducer;

    const State * Reducer::reduce(const State * previous, const Action & action) const {
      switch (action.type) {
        case ActionType::SET_STATE: {
          return memory.create(action.payload<Params>());
        }
        default:
          return previous;
      }
    }

  }
}
