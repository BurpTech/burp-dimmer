#pragma once

#include <ArduinoJson.h>
#include <Json/Deserializer.hpp>
#include <Redux/Reducer.hpp>
#include <Redux/Action.hpp>
#include "../../../ActionType.hpp"
#include "./State.hpp"

namespace Config {
  namespace Network {
    namespace Station {

      class Reducer : public Redux::Reducer<State, ActionType, JsonObject> {

        public:

          const State * init(const State * previous, const Redux::Reducer<State, ActionType, JsonObject>::f_withInit withInit) const override;
          const State * reduce(const State *previous, const Redux::Action<ActionType> &action) const override;

      };

    }
  }
}
