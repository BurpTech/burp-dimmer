#pragma once

#include "./Reducer.hpp"

namespace Redux {

  template <class State, class ActionType, class InitParams>
  class ReducerMap : public Reducer<State, ActionType, InitParams> {

    public:

      const State * init(const State * previous, const InitParams & initParams) const override {
        return Reducer<State, ActionType, InitParams>::alloc(
          previous,
          [&](void * address) {
            return new(address) State(previous, initParams);
          }
        );
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
