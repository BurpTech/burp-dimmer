#pragma once

#include <ArduinoJson.h>
#include <Json/Deserializer.hpp>
#include <Redux/Reducer.hpp>
#include <Redux/State.hpp>
#include <Redux/Action.hpp>
#include "../../../ActionType.hpp"
#include "./State.hpp"
#include "ArduinoJson.hpp"

namespace Config {
  namespace Network {
    namespace AccessPoint {

      class Reducer : public Redux::Reducer<State, ActionType, JsonObject> {

        public:

          const Redux::State * init(const Redux::State * state, const Redux::Reducer<State, ActionType, JsonObject>::f_withInit withInit) const override;
          const Redux::State * reduce(const Redux::State *state, const Redux::Action<ActionType> &action) const override;

      };

    }
  }
}
