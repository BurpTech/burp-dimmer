#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Light {

    const State * Reducer::init(const State * previous, const State & initialState) const {
      return _update(previous, initialState);
    }

    const State * Reducer::reduce(const State * previous, const Action & action) const {
      switch (action.type) {
        case ActionType::SET_STATE: {
          return _update(previous, *(action.payload<State>());
        }
        default:
          return previous;
      }
    }

  }
}
