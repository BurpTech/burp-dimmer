#pragma once

#include "./Reducer.hpp"
#include "./ReducerMapMacros.hpp"

namespace Redux {

  template <class DerivedState, class ActionType>
  class ReducerMap : public Reducer<DerivedState, ActionType> {

    public:

      const State * init(const State * state) const override {
        return new DerivedState(state->as<DerivedState>());
      }

      const State * reduce(const State * state, const Action<ActionType> & action) const override {
        return State::replace(state, new DerivedState(state->as<DerivedState>(), action));
      }

  };

}
