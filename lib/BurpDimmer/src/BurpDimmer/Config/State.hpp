#pragma once

#include <ArduinoJson.h>
#include "../Memory/Pair.hpp"
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

      class Instance {

        public:
          
          const Light::State::Instance * light;
          const Network::State::Instance * network;

          Instance(const Params * params);
          void serialize(JsonObject & object) const;

      };

      using Memory = Memory::Pair<Instance, Params>;
      extern Memory memory;

    }
  }
}
