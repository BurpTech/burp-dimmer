#pragma once

#include <BurpRedux/Store/Instance.hpp>
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Store {

      using Interface = BurpRedux::Store::Interface<State::Instance, State::Params>;

      template <size_t subscriberCount>
      using Instance = BurpRedux::Store::Instance<State::Instance, State::Params, subscriberCount>;

    }
  }
}
