#pragma once

#include <BurpRedux/Selector/Instance.hpp>
#include "../State.hpp"
#include "State.hpp"

#ifndef BURP_DIMMER_CONFIG_NETWORK_SUBSCRIBERS
#define BURP_DIMMER_CONFIG_NETWORK_SUBSCRIBERS 0
#endif

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      using Selector = BurpRedux::Selector::Instance<
        Config::State::Instance,
        State::Instance,
        BURP_DIMMER_CONFIG_NETWORK_SUBSCRIBERS
      >;

      extern Selector * selector;
      void init(const Config::State::Instance * state);
      void deinit();

    }
  }
}
