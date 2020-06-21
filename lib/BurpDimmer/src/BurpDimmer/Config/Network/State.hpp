#pragma once

#include <ArduinoJson.h>
#include "../../Memory/Pair.hpp"
#include "AccessPoint/State.hpp"
#include "Manager/State.hpp"
#include "Station/State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace State {

        constexpr char accessPointField[] = "accessPoint";
        constexpr char managerField[] = "manager";
        constexpr char stationField[] = "station";

        struct Params {
          const AccessPoint::State::Instance * accessPoint;
          const Manager::State::Instance * manager;
          const Station::State::Instance * station;
        };

        class Instance {

          public:
            
            const AccessPoint::State::Instance * accessPoint;
            const Manager::State::Instance * manager;
            const Station::State::Instance * station;

            Instance(const Params * params);
            void serialize(JsonObject & object) const;

        };

        using Memory = Memory::Pair<Instance, Params>;
        extern Memory memory;

      }
    }
  }
}
