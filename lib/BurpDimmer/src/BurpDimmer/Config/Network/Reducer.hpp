#pragma once

#include <BurpRedux/CombinedReducer.hpp>
#include <BurpRedux/SubState.hpp>
#include "AccessPoint/State.hpp"
#include "Manager/State.hpp"
#include "Station/State.hpp"
#include "State.hpp"

#define BURP_DIMMER_CONFIG_NETWORK_SUB_STATE(NAME, FIELD) BURP_REDUX_SUB_STATE(NAME, FIELD, Network::State::Instance, Network::State::Params, State::Instance, State::Params)

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      template <size_t mappingCount>
      using Reducer = BurpRedux::CombinedReducer<State::Instance, State::Params, mappingCount>;

      namespace AccessPoint {
        // define the ReducerMapping and Selector classes
        BURP_DIMMER_CONFIG_NETWORK_SUB_STATE(accessPoint, Network::State::accessPointField);
      }

      namespace Manager {
        // define the ReducerMapping and Selector classes
        BURP_DIMMER_CONFIG_NETWORK_SUB_STATE(manager, Network::State::managerField);
      }

      namespace Station {
        // define the ReducerMapping and Selector classes
        BURP_DIMMER_CONFIG_NETWORK_SUB_STATE(station, Network::State::stationField);
      }

    }
  }
}
