#pragma once

#include <ArduinoJson.h>
#include <BurpTree/State.hpp>
#include <BurpTree/Factory.hpp>
#include "Types.hpp"

namespace BurpDimmer {
  namespace Light {

    class State : public BurpTree::State {

      public:

        const bool on;
        const LevelIndex level;
        const Level pwm;
        const Delay saveStateDelay;

        State(
            const bool on,
            const LevelIndex level,
            const Level pwm,
            const Delay saveStateDelay
        );
        bool serialize(const JsonVariant & serialized) const override;

    };

  }
}
