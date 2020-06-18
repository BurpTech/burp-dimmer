#pragma once

#include <ArduinoJson.h>
#include <Json/Serializer.hpp>
#include <Redux/State.hpp>

namespace BurpDimmer {
  namespace Light {

    constexpr char onField[] = "on";
    constexpr char levelField[] = "level";
    constexpr char pwmField[] = "pwm";

    class State : public Redux::State, public Json::Serializer {
      public:

        bool on;
        unsigned char level;
        unsigned char pwm;

        State();
        State(const bool on, const unsigned char level, const unsigned char pwm);
        State(const State & state);
        State(const State * previous, const State & next);
        State(const State * previous, const bool on, const unsigned char level, const unsigned char pwm);
        void serialize(JsonObject & object) const override;

    };

  }
}
