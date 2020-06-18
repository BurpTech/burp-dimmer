#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        const Reducer reducer;

        const State * Reducer::reduce(const State * previous, const Action & action) const {
          switch (action.type) {
            case ActionType::NETWORK_ACCESS_POINT_SET_CONFIG: {
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
