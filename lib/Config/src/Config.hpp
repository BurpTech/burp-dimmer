#pragma once

#include <Redux/Store.hpp>
#include <Redux/ReducerMap.hpp>
#include "./ActionType.hpp"
#include "./Config/Network.hpp"
#include "ArduinoJson.hpp"

namespace Config {

    class State : public Redux::State {
      public:
        const Network::State * network;

        State(const State * previous, const JsonObject * object) :
          network(Network::reducer.init(
            previous ? previous->network : nullptr,
            [&](const Redux::Reducer<Network::State, ActionType, JsonObject>::f_doInit doInit) {
              const JsonObject obj = (*object)["network"];
              return doInit(&obj);
            }
          )->as<Network::State>()) {
        }

        State(const State * previous, const Redux::Action<ActionType> & action) :
          network(Network::reducer.reduce(previous, action)->as<Network::State>()) {
        }
    };
    extern const Redux::ReducerMap<State, ActionType, JsonObject> reducer;
    extern Redux::Store<State, ActionType, JsonObject> store;

}
