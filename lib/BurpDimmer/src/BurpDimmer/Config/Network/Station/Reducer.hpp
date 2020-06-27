#pragma once

#include <BurpRedux/Reducer/Instance.hpp>
#include "../../ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        using Reducer = BurpRedux::Reducer::Instance<State::Instance, State::Params, ActionType::NETWORK_STATION_SET_STATE>;

      }
    }
  }
}
