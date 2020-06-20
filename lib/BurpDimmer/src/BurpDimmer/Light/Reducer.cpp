#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Light {

    const Reducer reducer(memory);

    Reducer::Reducer(Memory & memory) :
      _memory(memory)
    {}

    const State * Reducer::reduce(const State * previous, const Action & action) const {
      switch (action.type) {
        case ActionType::SET_STATE: {
          return _memory.create(action.payload<Params>());
        }
        default:
          return previous;
      }
    }

  }
}
