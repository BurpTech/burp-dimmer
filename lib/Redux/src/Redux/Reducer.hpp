#pragma once

#include <functional>
#include "./State.hpp"
#include "./Action.hpp"

namespace Redux {

  template <class DerivedState, class ActionType, class InitParams>
  class Reducer {

    public:

      using f_doInit = std::function<const DerivedState * (const InitParams * initParams)>;
      using f_withInit = std::function<const DerivedState * (const f_doInit doInit)>;

      virtual const State * init(const State * state, const f_withInit withInit) const = 0;
      virtual const State * reduce(const State * state, const Action<ActionType> & action) const = 0;

    protected:

      using f_alloc = std::function<const DerivedState * (void * address)>;

      const DerivedState * _alloc(const DerivedState * previous, f_alloc alloc) const {
        if (previous != nullptr && previous != state1  && previous != state2) {
          printf("\n\n\nWhat the F!!!!!!!!!!!!!\n");
          printf("previous: %p\n", previous);
          printf("\n\n\n");
        }
        void * next = (previous == state1 ? state2 : state1);
        alloc(next);
        if (previous) {
          previous->~DerivedState();
        }
        return static_cast<DerivedState *>(next);
      }

    private:

      void * state1 = ::operator new(sizeof(DerivedState));
      void * state2 = ::operator new(sizeof(DerivedState));

  };
}
