#pragma once

#include <ArduinoJson.h>
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

      class Instance {

        public:

          const bool on;
          const unsigned char level;
          const unsigned char pwm;
          const Config * config;

          Instance(const Params * params);
          void serialize(JsonObject & object) const;

      };

      using Memory = Memory::Pair<Instance, Params>;
      extern Memory memory;

    }
  }
}
