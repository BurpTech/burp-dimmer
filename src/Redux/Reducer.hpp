#pragma once

#include "./State.hpp"
#include "./Action.hpp"

namespace Redux {

  template <class ActionType>
  class Reducer {

    public:

      virtual const State * init() const = 0;
      virtual const State * reduce(const State * state, const Action<ActionType> & action) const = 0;

  };
}
