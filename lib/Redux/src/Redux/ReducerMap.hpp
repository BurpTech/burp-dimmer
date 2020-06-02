#pragma once

#include "./Reducer.hpp"
#include "./ReducerMapMacros.hpp"

namespace Redux {

  template <class DerivedState, class ActionType, class InitParams>
  class ReducerMap : public Reducer<DerivedState, ActionType, InitParams> {

    public:

      const State * init(const State * state, const typename Reducer<DerivedState, ActionType, InitParams>::f_withInit withInit) const override {
        if (withInit) {
          return withInit([&](const InitParams * initParams) {
            return Reducer<DerivedState, ActionType, InitParams>::_alloc(
              state->as<DerivedState>(),
              [&](void * address) {
                return new(address) DerivedState(state->as<DerivedState>(), initParams);
              }
            );
          });
        } else {
          return Reducer<DerivedState, ActionType, InitParams>::_alloc(
            state->as<DerivedState>(),
            [&](void * address) {
              return new(address) DerivedState(state->as<DerivedState>(), nullptr);
            }
          );
        }
      }

      const State * reduce(const State * state, const Action<ActionType> & action) const override {
        return Reducer<DerivedState, ActionType, InitParams>::_alloc(
          state->as<DerivedState>(),
          [&](void * address) {
            return new(address) DerivedState(state->as<DerivedState>(), action);
          }
        );
      }

  };

}
