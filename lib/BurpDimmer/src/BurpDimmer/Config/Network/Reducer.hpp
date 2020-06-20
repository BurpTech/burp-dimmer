#pragma once

#include <CppRedux/Reducer.hpp>
#include "../ActionType.hpp"
#include "AccessPoint/Reducer.hpp"
#include "Manager/Reducer.hpp"
#include "Station/Reducer.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      class Reducer : public CppRedux::Reducer<State, Action> {

        public:

          Reducer(
              Memory & memory,
              const AccessPoint::Reducer & accessPointReducer,
              const Manager::Reducer & managerReducer,
              const Station::Reducer & stationReducer
          );
          const State * reduce(const State * previous, const Action & action) const override;

        private:

          Memory & _memory;
          const AccessPoint::Reducer & _accessPointReducer;
          const Manager::Reducer & _managerReducer;
          const Station::Reducer & _stationReducer;

      };

      extern const Reducer reducer;

    }
  }
}
