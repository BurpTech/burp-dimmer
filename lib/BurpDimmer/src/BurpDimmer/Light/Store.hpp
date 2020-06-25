#pragma once

#include <BurpRedux/Store/Instance.hpp>
#include "State.hpp"
#include "../defines.hpp"

namespace BurpDimmer {
  namespace Light {

    using Store = BurpRedux::Store::Instance<State::Instance, BURP_DIMMER_LIGHT_SUBSCRIBERS>;

  }
}
