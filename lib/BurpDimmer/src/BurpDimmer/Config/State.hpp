#pragma once

#include <ArduinoJson.h>
#include <BurpRedux/State/Instance.hpp>
#include <BurpRedux/Creator/Instance.hpp>
#include "Light/State.hpp"
#include "Network/State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace State {

      constexpr char lightField[] = "light";
      constexpr char networkField[] = "network";

      struct Params {
        Light::State::Params light;
        Network::State::Params network;
      };

      class Instance : public BurpRedux::State::Instance {

        public:
          
          const Light::State::Instance * light;
          const Network::State::Instance * network;

          Instance();
          Instance(const Instance & instance, const unsigned long uid);
          void serialize(const JsonObject & object) const override;

      };

      using Creator = BurpRedux::Creator::Instance<Instance, Instance>;

    }
  }
}
