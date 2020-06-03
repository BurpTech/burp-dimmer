#pragma once

#include <Redux/Store.hpp>
#include <Redux/ReducerMap.hpp>
#include "./ActionType.hpp"
#include "./Config/Network.hpp"
#include "ArduinoJson.hpp"

namespace Config {

    class State {
      public:
        const Network::State * network;
        State(const State * previous, const JsonObject & object);
        State(const State * previous, const Redux::Action<ActionType> & action);
    };
    extern const Redux::ReducerMap<State, ActionType, JsonObject> reducer;
    extern Redux::Store<State, ActionType, JsonObject> store;

}
