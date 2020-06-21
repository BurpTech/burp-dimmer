#pragma once

#include <BurpRedux/Reducer.hpp>
#include "ActionType.hpp"
#include "Light/Reducer.hpp"
#include "Network/Reducer.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {

    class Reducer : public BurpRedux::Reducer<State::Instance, Action> {

      public:

        Reducer(
            State::Memory & memory,
            Network::Reducer & networkReducer,
            Light::Reducer & lightReducer
        );
        const State::Instance * reduce(const State::Instance * previous, const Action & action) override;

      private:

        State::Memory & _memory;
        Network::Reducer & _networkReducer;
        Light::Reducer & _lightReducer;

    };

    extern Reducer reducer;

  }
}
