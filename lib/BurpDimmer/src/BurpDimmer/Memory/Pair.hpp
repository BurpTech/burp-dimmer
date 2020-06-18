#pragma once

#include <memory>

namespace BurpDimmer {
  namespace Memory {

    template <class State, class Params>
    class Pair {

      public:

        const State * create(Params * params) {
          _current++;
          _current %= 2;
          return new(_pair[_current]) State(params);
        }

      private:

        std::allocator<State> allocator;
        State * _pair = allocator.allocate(2);
        size_t _current = 1;

    };

  }
}
