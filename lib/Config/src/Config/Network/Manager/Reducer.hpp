#pragma once

#include <ArduinoJson.h>
#include <Json/Deserializer.hpp>
#include <Redux/Reducer.hpp>
#include <Redux/Action.hpp>
#include "../../../ActionType.hpp"
#include "./State.hpp"

namespace Config {
  namespace Network {
    namespace Manager {

      class Reducer : public Redux::Reducer<State, ActionType, JsonObject> {

        public:

          const State * init(const State * previous, const f_withInit withInit) const override;
          const State * reduce(const State *previous, const Redux::Action<ActionType> &action) const override;

        private:

          static const State * _createNextPermMode(void * address, const State & previous);

      };

    }
  }
}
