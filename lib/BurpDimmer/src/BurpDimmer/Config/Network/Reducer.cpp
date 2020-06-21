#include "Reducer.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      Reducer reducer(State::memory, AccessPoint::reducer, Manager::reducer, Station::reducer);

      Reducer::Reducer(
          State::Memory & memory,
          AccessPoint::Reducer & accessPointReducer,
          Manager::Reducer & managerReducer,
          Station::Reducer & stationReducer
      ) :
        _memory(memory),
        _accessPointReducer(accessPointReducer),
        _managerReducer(managerReducer),
        _stationReducer(stationReducer)
      {}

      const State::Instance * Reducer::reduce(const State::Instance * previous, const Action & action) {
        const AccessPoint::State::Instance * accessPoint = _accessPointReducer.reduce(previous->accessPoint, action);
        const Manager::State::Instance * manager = _managerReducer.reduce(previous->manager, action);
        const Station::State::Instance * station = _stationReducer.reduce(previous->station, action);
        if (
          accessPoint != previous->accessPoint ||
          manager != previous->manager ||
          station != previous->station
        ) {
          const State::Params params = {
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
