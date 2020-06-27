#pragma once

#include <BurpRedux/Reducer/Instance.hpp>
#include "../../ActionType.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        using Reducer = BurpRedux::Reducer::Instance<State::Instance, State::Params, ActionType::NETWORK_ACCESS_POINT_SET_STATE>;

      }
    }
  }
}
