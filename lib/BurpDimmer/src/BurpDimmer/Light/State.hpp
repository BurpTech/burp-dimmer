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
            const Config * config,
            const bool on,
            const Level level,
            const Pwm pwm
        );
        State(const Config * config);
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

        bool createDefault() override;
        bool deserialize(const JsonObject & serialized) override ;
        bool applyConfig(const Config * config);
        bool toggle();
        bool increaseBrightness();
        bool decreaseBrightness();

      private:

        const Config * _config;

        const State * _applyConfig(
            const bool on,
            const State::Level level,
            const State::Pwm pwm
        );

    };

  }
}
