#pragma once

#include "../../Json/Serializer.hpp"
#include "../../Memory/Pair.hpp"
#include "AccessPoint/State.hpp"
#include "Manager/State.hpp"
#include "Station/State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      constexpr char accessPointField[] = "accessPoint";
      constexpr char managerField[] = "manager";
      constexpr char stationField[] = "station";

      struct Params {
        const AccessPoint::State * accessPoint;
        const Manager::State * manager;
        const Station::State * station;
      };

      class State : public Json::Serializer {

        public:
          
          const AccessPoint::State * accessPoint;
          const Manager::State * manager;
          const Station::State * station;

          State(const Params * params);
          void serialize(JsonObject & object) const override;

      };

      using Memory = Memory::Pair<State, Params>;
      extern Memory memory;

    }
  }
}
