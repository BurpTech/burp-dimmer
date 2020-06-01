#pragma once

#include "./Reducer.hpp"
#include "./ReducerMapMacros.hpp"

namespace Redux {

  template <class ActionType, class DerivedState>
  class ReducerMap : public Reducer<ActionType> {

    public:

      const State * init() const override {
        return new DerivedState;
      }

      const State * reduce(const State * state, const Action<ActionType> & action) const override {
        return State::replace(state, new DerivedState(state->as<DerivedState>(), action));
      }

  };

}
