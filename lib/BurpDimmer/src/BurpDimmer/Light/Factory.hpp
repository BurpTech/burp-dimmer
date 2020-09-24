#pragma once

#include <BurpTree/Factory.hpp>
#include "Status.hpp"
#include "State.hpp"
#include "Types.hpp"

namespace BurpDimmer {
  namespace Light {

    class Factory : public BurpTree::Factory<State, Status> {

      public:

        void setConfig(const Config * config);

        bool deserialize(const JsonVariant & serialized) override ;
        bool createDefault() override;
        bool applyConfig(const Config * config);
        bool toggle();
        bool increaseBrightness();
        bool decreaseBrightness();

      private:

        const Config * _config;

        const State * _applyConfig(
            const bool on,
            const LevelIndex level,
            const Level pwm
        );

    };

  }
}
