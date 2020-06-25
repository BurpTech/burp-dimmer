#pragma once

#include <memory>
#include <BurpRedux/Creator/Interface.hpp>

namespace BurpDimmer {
  namespace Memory {

    template <class State, class Params>
    class Pair : public BurpRedux::Creator::Interface<State, Params> {

      public:

        const State * create(const State * previous, const Params * params) {
          _current++;
          _current %= 2;
          _sequenceId++;
          return new(&(_pair[_current])) State(params, _sequenceId);
        }

      private:

        std::allocator<State> allocator;
        State * _pair = allocator.allocate(2);
        size_t _current = 1;
        unsigned long _sequenceId = 0;

    };

  }
}
