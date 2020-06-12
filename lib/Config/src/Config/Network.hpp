#pragma once

#include <Redux/ReducerMap.hpp>
#include <ArduinoJson.h>
#include <Json/Serializer.hpp>

#include "ActionType.hpp"
#include "Network/Manager.hpp"
#include "Network/Station.hpp"
#include "Network/AccessPoint.hpp"

namespace Config {
  namespace Network {

    class State : public Json::Serializer {
      public:
        const Manager::State * manager;
        const Station::State * station;
        const AccessPoint::State * accessPoint;
        State(const State * previous, const JsonObject & object);
        State(const State * previous, const Action & action);
        void serialize(JsonObject & object) const override;
    };

    using Reducer = Redux::ReducerMap<State, ActionType, JsonObject>;
    extern const Reducer reducer;

  }
}
