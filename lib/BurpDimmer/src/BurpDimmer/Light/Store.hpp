#pragma once

#include <BurpRedux/Store/Instance.hpp>
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {
    namespace Store {

      using Interface = BurpRedux::Store::Interface<State::Instance>;

      template <size_t subscriberCount>
      using Instance = BurpRedux::Store::Instance<State::Instance, subscriberCount>;

    }
  }
}
