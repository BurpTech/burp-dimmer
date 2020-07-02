#pragma once

#include <ArduinoJson.h>
#include <BurpTree/State.hpp>
#include <BurpTree/Status.hpp>
#include <BurpTree/Factory.hpp>
#include "Config.hpp"

namespace BurpDimmer {
  namespace Light {

    class State : public BurpTree::State {

      public:

        using Level = Config::Level;
        using Pwm = unsigned char;

        const Config * config;
        const bool on;
        const Level level;
        const Pwm pwm;

        State(
            const Uid uid,
            const Config * config,
            const bool on,
            const Level level,
            const Pwm pwm
        );
        State(const Uid uid, const Config * config);
        void serialize(const JsonObject & object) const override;

    };

    class Status : public BurpTree::Status {
      public:
        enum : BurpTree::Status::Code {
          ok,
          noObject,
          maxLevels,
          outOfRange,
          invalidOn,
          invalidLevel,
          invalidPwm,
          maxBrightness,
          minBrightness
        };
        const char * c_str() const override;
    };

    class Factory : public BurpTree::Factory<State, Status> {

      public:

        void setConfig(const Config * config);

        const BurpTree::State * deserialize(const JsonObject & serialized) override ;
        const BurpTree::State * applyConfig(const Config * config);
        const BurpTree::State * toggle();
        const BurpTree::State * increaseBrightness();
        const BurpTree::State * decreaseBrightness();

      private:

        const Config * _config;

        const State * _applyConfig(
            const bool on,
            const State::Level level,
            const State::Pwm pwm
        );

        const State * _default() override;

    };

  }
}
