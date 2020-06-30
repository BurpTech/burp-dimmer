#pragma once

#include <ArduinoJson.h>
#include <BurpTree/State.hpp>
#include <BurpTree/Status.hpp>
#include <BurpTree/Factory.hpp>
#include "Config.hpp"

namespace BurpDimmer {
  namespace Light {

      constexpr char onField[] = "on";
      constexpr char levelField[] = "level";
      constexpr char pwmField[] = "pwm";

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

      class Factory : public BurpTree::Factory<State> {

        public:

          void setInitialConfig(const Config * config);

          const BurpTree::Status & getStatus() const override;
          const BurpTree::State * deserialize(const JsonObject & serialized) override ;

          const BurpTree::State * applyConfig(const Config * config);
          const BurpTree::State * toggle();
          const BurpTree::State * increaseBrightness();
          const BurpTree::State * decreaseBrightness();

        private:

          class Status : public BurpTree::Status {
            public:
              using Level = BurpTree::Status::Level;
              enum Code : BurpTree::Status::Code {
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
              const char * c_str() const override;
          };

          const Config * _initialConfig;
          Status _status;

          static const BurpTree::State * _applyConfig(
              const Uid uid,
              void * address,
              const Config * config,
              const bool on,
              const State::Level level,
              const State::Pwm pwm
          );

          const BurpTree::State * _fail(const Uid uid, void * address, const Status::Code code);

      };

    }
  }
}
