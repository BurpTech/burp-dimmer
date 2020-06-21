#pragma once

#include "../Json/Serializer.hpp"
#include "../Memory/Pair.hpp"

namespace BurpDimmer {
  namespace Light {

    constexpr char onField[] = "on";
    constexpr char levelField[] = "level";
    constexpr char pwmField[] = "pwm";

    struct Params {
      const bool on;
      const unsigned char level;
      const unsigned char pwm;
    };

    class State {

      public:

        const bool on;
        const unsigned char level;
        const unsigned char pwm;

        State(const Params * params);
        void serialize(JsonObject & object) const;

    };

    using Memory = Memory::Pair<State, Params>;
    extern Memory memory;

  }
}