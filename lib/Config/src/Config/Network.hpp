#pragma once

#include <Redux/ReducerMap.hpp>
#include <ArduinoJson.h>
#include <Json/Serializer.hpp>

#include "../ActionType.hpp"
#include "./Network/Manager.hpp"
#include "./Network/Station.hpp"
#include "./Network/AccessPoint.hpp"

namespace Config {
  namespace Network {

    class State : public Json::Serializer {
      public:
        static constexpr char MANAGER_FIELD[] = "manager";
        static constexpr char STATION_FIELD[] = "station";
        static constexpr char ACCESS_POINT_FIELD[] = "accessPoint";
        const Manager::State * manager;
        const Station::State * station;
        const AccessPoint::State * accessPoint;
        State(const State * previous, const JsonObject & object);
        State(const State * previous, const Redux::Action<ActionType> & action);
        void serialize(JsonObject & object) const override;
    };
    extern const Redux::ReducerMap<State, ActionType, JsonObject> reducer;

  }
}
