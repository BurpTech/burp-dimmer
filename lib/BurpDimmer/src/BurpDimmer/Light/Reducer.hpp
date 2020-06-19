#pragma once

#include <Redux/Reducer.hpp>
#include "ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    class Reducer : public Redux::Reducer<State, ActionType> {

      public:

        const State * reduce(const State * previous, const Action & action) const override;

    };

  }
}
