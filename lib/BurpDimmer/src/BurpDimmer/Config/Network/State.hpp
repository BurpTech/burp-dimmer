#pragma once

#include <ArduinoJson.h>
#include <BurpRedux/State/Instance.hpp>
#include <BurpRedux/Creator/Instance.hpp>
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

        class Instance : public BurpRedux::State::Instance {

          public:
            
            const AccessPoint::State::Instance * accessPoint;
            const Manager::State::Instance * manager;
            const Station::State::Instance * station;

            Instance(const Params * params, const unsigned long uid);
            void serialize(JsonObject & object) const;

        };

        using Creator = BurpRedux::Creator::Instance<Instance, Params>;

      }
    }
  }
}
