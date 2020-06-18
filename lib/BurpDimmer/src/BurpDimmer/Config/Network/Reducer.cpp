#include "AccessPoint/Reducer.hpp"
#include "Manager/Reducer.hpp"
#include "Station/Reducer.hpp"
#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      const Reducer reducer;

      const State * Reducer::reduce(const State * previous, const Action & action) const {
        const AccessPoint::State * accessPoint = AccessPoint::reducer.reduce(previous->accessPoint, action);
        const Manager::State * manager = Manager::reducer.reduce(previous->manager, action);
        const Station::State * station = Station::reducer.reduce(previous->station, action);
        if (
          accessPoint != previous->accessPoint ||
          manager != previous->manager ||
          station != previous->station
        ) {
          const Params params = {
            accessPoint,
            manager,
            station
          };
          return memory.create(&params);
        }
        return previous;
      }

    }
  }
}
