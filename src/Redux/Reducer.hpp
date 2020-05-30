#ifndef Redux_Reducer_hpp
#define Redux_Reducer_hpp

#include <functional>

#include "./State.hpp"
#include "./Action.hpp"

namespace Redux {
  class Reducer {

    public:

      virtual const State * init() const = 0;
      virtual const State * reduce(const State * state, const Action & action) const = 0;

  };
}

#endif
