#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        const Reducer reducer;

        const State * Reducer::reduce(const State * previous, const Action & action) const {
          switch (action.type) {
            case ActionType::NETWORK_STATION_SET_STATE: {
              return memory.create(action.payload<Params>());
            }
            default:
              return previous;
          }
        }

      }
    }
  }
}
