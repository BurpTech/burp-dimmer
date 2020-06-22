#pragma once

#include <BurpRedux/Selector/Instance.hpp>
#include "../State.hpp"
#include "State.hpp"
#include "../../../defines.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        using Selector = BurpRedux::Selector::Instance<
          Network::State::Instance,
          State::Instance,
          BURP_DIMMER_CONFIG_NETWORK_STATION_SUBSCRIBERS
        >;

        extern Selector * selector;
        void init(const Network::State::Instance * state);
        void deinit();
        void reportSubscriberCounts();

      }
    }
  }
}
