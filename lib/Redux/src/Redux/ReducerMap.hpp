#pragma once

#include "./Reducer.hpp"

namespace Redux {

  template <class State, class ActionType, class InitParams>
  class ReducerMap : public Reducer<State, ActionType, InitParams> {

    public:

      const State * init(const State * previous, const typename Reducer<State, ActionType, InitParams>::f_withInit withInit) const override {
        return withInit([&](const InitParams * initParams) {
          return Reducer<State, ActionType, InitParams>::alloc(
            previous,
            [&](void * address) {
              return new(address) State(previous, initParams);
            }
          );
        });
      }

      const State * reduce(const State * previous, const Action<ActionType> & action) const override {
        return Reducer<State, ActionType, InitParams>::alloc(
          previous,
          [&](void * address) {
            return new(address) State(previous, action);
          }
        );
      }

  };

}
