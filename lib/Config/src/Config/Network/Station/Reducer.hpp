#pragma once

#include <ArduinoJson.h>
#include <Json/Deserializer.hpp>
#include <Redux/Reducer.hpp>
#include <Redux/Action.hpp>
#include "../../../ActionType.hpp"
#include "./State.hpp"
#include "ArduinoJson.hpp"

namespace Config {
  namespace Network {
    namespace Station {

      class Reducer : public Redux::Reducer<State, ActionType, JsonObject> {

        public:

          const State * init(const State * previous, const JsonObject & object) const override;
          const State * reduce(const State *previous, const Redux::Action<ActionType> &action) const override;

      };

    }
  }
}
