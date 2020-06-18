#pragma once

#include <Json/Serializer.hpp>
#include <Memory/Pair.hpp>
#include "Light/State.hpp"
#include "Network/State.hpp"

namespace BurpDimmer {
  namespace Config {

    constexpr char lightField[] = "light";
    constexpr char networkField[] = "network";

    struct Params {
      const Light::State * light;
      const Network::State * network;
    };

    class State : public Json::Serializer {

      public:
        
        const Light::State * light;
        const Network::State * network;

        State(const Params * params);
        void serialize(JsonObject & object) const override;

    };

    extern Memory::Pair<State, Params> memory;

  }
}
