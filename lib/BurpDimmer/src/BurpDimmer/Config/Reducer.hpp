#pragma once

#include <CppRedux/Reducer.hpp>
#include "ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {

    class Reducer : public CppRedux::Reducer<State, Action> {

      public:

        const State * reduce(const State * previous, const Action & action) const override;

    };

    extern const Reducer reducer;

  }
}
