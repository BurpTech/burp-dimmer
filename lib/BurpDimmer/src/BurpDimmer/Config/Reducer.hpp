#pragma once

#include <BurpRedux/CombinedReducer.hpp>
#include <BurpRedux/SubState.hpp>
#include "Light/State.hpp"
#include "Network/State.hpp"
#include "State.hpp"

#define BURP_DIMMER_CONFIG_SUB_STATE(NAME, FIELD) BURP_REDUX_SUB_STATE(NAME, FIELD, Config::State::Instance, Config::State::Params, State::Instance, State::Params)

namespace BurpDimmer {
  namespace Config {

    template <size_t mappingCount>
    using Reducer = BurpRedux::CombinedReducer<State::Instance, State::Params, mappingCount>;

    namespace Light {
      // define the ReducerMapping and Selector classes
      BURP_DIMMER_CONFIG_SUB_STATE(light, Config::State::lightField);
    }

    namespace Network {
      // define the ReducerMapping and Selector classes
      BURP_DIMMER_CONFIG_SUB_STATE(network, Config::State::networkField);
    }

  }
}
