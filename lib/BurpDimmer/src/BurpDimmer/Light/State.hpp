#pragma once

#include <ArduinoJson.h>
#include <BurpRedux/State/Instance.hpp>
#include <BurpRedux/Creator/Instance.hpp>
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

      class Instance : public BurpRedux::State::Instance {

        public:

          const bool on;
          const unsigned char level;
          const unsigned char pwm;
          const Config * config;

          Instance(const Params * params, const unsigned long uid);
          void serialize(JsonObject & object) const;

      };

      using Creator = BurpRedux::Creator::Instance<Instance, Params>;

    }
  }
}
