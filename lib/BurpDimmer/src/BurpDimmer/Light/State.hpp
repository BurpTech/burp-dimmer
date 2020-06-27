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

      enum class Error {
        noError,
        noObject,
        maxLevels,
        outOfRange,
        invalidOn,
        invalidLevel,
        invalidPwm,
        maxBrightness,
        minBrightness
      };

      struct Params {
        Error error;
        const Config * config;
        bool on;
        unsigned char level;
        unsigned char pwm;
      };

      class Instance : public BurpRedux::State::Instance {

        public:

          const bool on;
          const unsigned char level;
          const unsigned char pwm;
          const Config * config;

          Instance(const Params & params, const unsigned long uid);
          void serialize(const JsonObject & object) const override;

      };

      using Creator = BurpRedux::Creator::Instance<Instance, Params>;

    }
  }
}
