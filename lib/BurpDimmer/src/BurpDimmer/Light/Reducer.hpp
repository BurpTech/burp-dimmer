#pragma once

#include <BurpRedux/Reducer.hpp>
#include "ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    class Reducer : public BurpRedux::Reducer<State::Instance, Action> {

      public:

        Reducer(State::Memory & memory);
        const State::Instance * reduce(const State::Instance * previous, const Action & action) override;

      private:

        State::Memory & _memory;

    };

    extern Reducer reducer;

  }
}
