#pragma once

#include <BurpRedux/Selector/Instance.hpp>
#include "../State.hpp"
#include "State.hpp"
#include "../../defines.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      using Selector = BurpRedux::Selector::Instance<
        Config::State::Instance,
        State::Instance,
        BURP_DIMMER_CONFIG_NETWORK_SUBSCRIBERS
      >;

      extern Selector selector;
      void setup(const Config::State::Instance * state);
      void reportSubscriberCounts();

    }
  }
}
