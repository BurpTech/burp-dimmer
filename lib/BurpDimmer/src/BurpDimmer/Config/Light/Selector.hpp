#pragma once

#include <BurpRedux/Selector/Instance.hpp>
#include "../State.hpp"
#include "State.hpp"
#include "../../defines.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      using Selector = BurpRedux::Selector::Instance<
        Config::State::Instance,
        State::Instance,
        BURP_DIMMER_CONFIG_LIGHT_SUBSCRIBERS
      >;

      extern Selector * selector;
      void init(const Config::State::Instance * state);
      void deinit();
      void reportSubscriberCounts();

    }
  }
}
