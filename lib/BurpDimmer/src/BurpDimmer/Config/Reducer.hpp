#pragma once

#include <CppRedux/Reducer.hpp>
#include "ActionType.hpp"
#include "Light/Reducer.hpp"
#include "Network/Reducer.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {

    class Reducer : public CppRedux::Reducer<State, Action> {

      public:

        Reducer(
            Memory & memory,
            const Network::Reducer & networkReducer,
            const Light::Reducer & lightReducer
        );
        const State * reduce(const State * previous, const Action & action) const override;

      private:

        Memory & _memory;
        const Network::Reducer & _networkReducer;
        const Light::Reducer & _lightReducer;

    };

    extern const Reducer reducer;

  }
}
