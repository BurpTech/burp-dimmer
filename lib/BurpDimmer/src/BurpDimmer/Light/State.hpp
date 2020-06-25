#pragma once

#include <ArduinoJson.h>
#include <BurpRedux/State/Interface.hpp>
#include "../Memory/Pair.hpp"
#include "Config.hpp"

namespace BurpDimmer {
  namespace Light {
    namespace State {

      constexpr char onField[] = "on";
      constexpr char levelField[] = "level";
      constexpr char pwmField[] = "pwm";

      struct Fields {
        const bool on;
        const unsigned char level;
        const unsigned char pwm;
      };

      struct Params {
        const Config * config;
        const Fields * fields;
      };

      class Instance : public BurpRedux::State::Interface {

        public:

          const bool on;
          const unsigned char level;
          const unsigned char pwm;
          const Config * config;

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
