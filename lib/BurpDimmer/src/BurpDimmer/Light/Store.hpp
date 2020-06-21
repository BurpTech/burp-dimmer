#pragma once

#include <BurpRedux/Store/Instance.hpp>
#include "State.hpp"
#include "ActionType.hpp"

#ifndef BURP_DIMMER_LIGHT_SUBSCRIBERS
#define BURP_DIMMER_LIGHT_SUBSCRIBERS 0
#endif

namespace BurpDimmer {
  namespace Light {

    using Store = BurpRedux::Store::Instance<
      State::Instance,
      Action,
      BURP_DIMMER_LIGHT_SUBSCRIBERS
    >;

    extern Store * store;
    void init(const State::Instance * state);
    void deinit();

  }
}
