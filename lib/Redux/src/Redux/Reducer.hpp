#pragma once

#include <functional>
#include "./Action.hpp"

namespace Redux {

  template <class State, class ActionType, class InitParams>
  class Reducer {

    public:

      using f_doInit = std::function<const State * (const InitParams * initParams)>;
      using f_withInit = std::function<const State * (const f_doInit doInit)>;

      virtual const State * init(const State * previous, const f_withInit withInit) const = 0;
      virtual const State * reduce(const State * previous, const Action<ActionType> & action) const = 0;

      using f_alloc = std::function<const State * (void * address)>;

      const State * alloc(const State * previous, f_alloc alloc) const {
        const State * next = alloc(previous == state1 ? state2 : state1);
        if (previous) {
          previous->~State();
        }
        return next;
      }

    private:

      void * state1 = ::operator new(sizeof(State));
      void * state2 = ::operator new(sizeof(State));

  };
}
