#pragma once

#include <BurpRedux/Selector/Instance.hpp>
#include "../State.hpp"
#include "State.hpp"

#ifndef BURP_DIMMER_CONFIG_NETWORK_ACCESS_POINT_SUBSCRIBERS
#define BURP_DIMMER_CONFIG_NETWORK_ACCESS_POINT_SUBSCRIBERS 0
#endif

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        using Selector = BurpRedux::Selector::Instance<
          Network::State::Instance,
          State::Instance,
          BURP_DIMMER_CONFIG_NETWORK_ACCESS_POINT_SUBSCRIBERS
        >;

        extern Selector * selector;
        void init(const Network::State::Instance * state);
        void deinit();

      }
    }
  }
}
