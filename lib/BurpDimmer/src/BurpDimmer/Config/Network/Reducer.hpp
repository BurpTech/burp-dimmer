#pragma once

#include <Redux/Reducer.hpp>
#include "../ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      class Reducer : public Redux::Reducer<State, ActionType> {

        public:

          const State * reduce(const State * previous, const Action & action) const override;

      };

      extern const Reducer reducer;

    }
  }
}
