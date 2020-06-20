#include "Reducer.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        const Reducer reducer(memory);

        Reducer::Reducer(Memory & memory) :
          _memory(memory)
        {}

        const State * Reducer::reduce(const State * previous, const Action & action) const {
          switch (action.type) {
            case ActionType::NETWORK_MANAGER_SET_STATE: {
              return _memory.create(action.payload<Params>());
            }
            default:
              return previous;
          }
        }

      }
    }
  }
}
