#pragma once

#include <CppRedux/Reducer.hpp>
#include "../ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      class Reducer : public CppRedux::Reducer<State, Action> {

        public:

          Reducer(Memory & memory);
          const State * reduce(const State * previous, const Action & action) const override;

        private:

          Memory & _memory;

      };

      extern const Reducer reducer;

    }
  }
}
