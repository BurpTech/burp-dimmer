#pragma once

#include <BurpRedux/Reducer.hpp>
#include "../ActionType.hpp"
#include "AccessPoint/Reducer.hpp"
#include "Manager/Reducer.hpp"
#include "Station/Reducer.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      class Reducer : public BurpRedux::Reducer<State::Instance, Action> {

        public:

          Reducer(
              State::Memory & memory,
              AccessPoint::Reducer & accessPointReducer,
              Manager::Reducer & managerReducer,
              Station::Reducer & stationReducer
          );
          const State::Instance * reduce(const State::Instance * previous, const Action & action) override;

        private:

          State::Memory & _memory;
          AccessPoint::Reducer & _accessPointReducer;
          Manager::Reducer & _managerReducer;
          Station::Reducer & _stationReducer;

      };

      extern Reducer reducer;

    }
  }
}
