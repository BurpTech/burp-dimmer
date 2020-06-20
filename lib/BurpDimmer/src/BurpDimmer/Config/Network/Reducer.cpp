#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      const Reducer reducer(memory, AccessPoint::reducer, Manager::reducer, Station::reducer);

      Reducer::Reducer(
          Memory & memory,
          const AccessPoint::Reducer & accessPointReducer,
          const Manager::Reducer & managerReducer,
          const Station::Reducer & stationReducer
      ) :
        _memory(memory),
        _accessPointReducer(accessPointReducer),
        _managerReducer(managerReducer),
        _stationReducer(stationReducer)
      {}

      const State * Reducer::reduce(const State * previous, const Action & action) const {
        const AccessPoint::State * accessPoint = _accessPointReducer.reduce(previous->accessPoint, action);
        const Manager::State * manager = _managerReducer.reduce(previous->manager, action);
        const Station::State * station = _stationReducer.reduce(previous->station, action);
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
          return _memory.create(&params);
        }
        return previous;
      }

    }
  }
}
