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
        const Light::State::Instance * light;
        const Network::State::Instance * network;
      };

      class Instance : public BurpRedux::State::Instance {

        public:
          
          const Light::State::Instance * light;
          const Network::State::Instance * network;

          Instance(const Params * params, const unsigned long uid);
          void serialize(JsonObject & object) const;

      };

      using Creator = BurpRedux::Creator::Instance<Instance, Params>;

    }
  }
}
