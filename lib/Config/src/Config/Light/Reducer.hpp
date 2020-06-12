#pragma once

#include <ArduinoJson.h>
#include <Redux/Reducer.hpp>
#include "../ActionType.hpp"
#include "State.hpp"

namespace Config {
  namespace Light {

    class Reducer : public Redux::Reducer<State, ActionType, JsonObject> {

      public:

        const State * init(const State * previous, const JsonObject & object) const override;
        const State * reduce(const State * previous, const Action & action) const override;

    };

  }
}
