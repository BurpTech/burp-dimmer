#pragma once

#include <Redux/Store.hpp>
#include <Redux/ReducerMap.hpp>
#include <ArduinoJson.h>
#include <Json/Serializer.hpp>
#include "ActionType.hpp"
#include "Config/Network.hpp"

namespace Config {

    class State : public Json::Serializer {
      public:
        static constexpr char NETWORK_FIELD[] = "network";
        const Network::State * network;
        State(const State * previous, const JsonObject & object);
        State(const State * previous, const Redux::Action<ActionType> & action);
        void serialize(JsonObject & object) const override;
    };
    
    using Reducer = Redux::ReducerMap<State, ActionType, JsonObject>;
    using Store = Redux::Store<State, ActionType, JsonObject>;

    extern const Reducer reducer;
    extern Store store;

}
