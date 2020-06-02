#pragma once

#include <functional>
#include "./State.hpp"
#include "./Action.hpp"

namespace Redux {

  template <class DerivedState, class ActionType>
  class Reducer {

    public:

      virtual const State * init(const State * state) const = 0;
      virtual const State * reduce(const State * state, const Action<ActionType> & action) const = 0;

    protected:

      using f_alloc = std::function<const DerivedState * (void * address)>;

      void * _states[2] = {
        new char(sizeof(DerivedState)),
        new char(sizeof(DerivedState))
      };

      const DerivedState * _alloc(f_alloc alloc, const DerivedState * previous) const {
        const DerivedState * next = alloc(previous == _states[0] ? _states[1] : _states[0]);
        if (previous) {
          previous->~DerivedState();
        }
        return next;
      }

  };
}
