#pragma once

namespace Redux {
  template <class State>
  class Subscriber {

    public:

      virtual void notify(const State * state) = 0;

  };
}
