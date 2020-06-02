#pragma once

#include <ArduinoJson.h>
#include <Json/Deserializer.hpp>
#include <Redux/Reducer.hpp>
#include <Redux/State.hpp>
#include <Redux/Action.hpp>
#include "../../../ActionType.hpp"
#include "./State.hpp"

namespace Config {
  namespace Network {
    namespace Station {

      class Reducer : public Json::Deserializer, public Redux::Reducer<State, ActionType> {

        public:

          void deserialize(const JsonObject & object) override;
          const Redux::State * init(const Redux::State * state) const override;
          const Redux::State * reduce(const Redux::State *state, const Redux::Action<ActionType> &action) const override;

        private:

          const State * _initialState = nullptr;

      };

    }
  }
}
