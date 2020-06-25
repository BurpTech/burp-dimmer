#pragma once

#include <BurpRedux/Store/Instance.hpp>
#include "State.hpp"
#include "../defines.hpp"

namespace BurpDimmer {
  namespace Config {

    template <size_t subscriberCount>
    using Store = BurpRedux::Store::Instance<State::Instance, subscriberCount>;

  }
}
