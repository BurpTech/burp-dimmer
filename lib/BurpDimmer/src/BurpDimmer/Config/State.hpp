#pragma once

#include <ArduinoJson.h>
#include <BurpRedux/State/Interface.hpp>
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

      class Instance : public BurpRedux::State::Interface {

        public:
          
          const Light::State::Instance * light;
          const Network::State::Instance * network;

          Instance(const Params * params, unsigned long sequenceId);
          void serialize(JsonObject & object) const;
          unsigned long getUid() const override;

        private:

          unsigned long sequenceId;

      };

      using Memory = Memory::Pair<Instance, Params>;

    }
  }
}
