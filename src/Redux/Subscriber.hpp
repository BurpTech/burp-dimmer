#ifndef Redux_Subscriber_hpp
#define Redux_Subscriber_hpp

#include <functional>

#include "../Util/List.hpp"
#include "State.hpp"
#include "Action.hpp"

namespace Redux {
  class Subscriber {

    public:

      virtual void notify() const = 0;

  };
}

#endif
