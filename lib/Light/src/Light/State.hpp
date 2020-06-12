#pragma once

#include <ArduinoJson.h>
#include <Json/Serializer.hpp>

namespace Light {

  enum class Error {
    noError,
    outOfRange,
    invalidOn,
    invalidLevel,
    invalidPwm
  };

  enum class Change {
    increase,
    decrease
  };

  class State : public Json::Serializer {
    public:

      bool on;
      unsigned char level;
      unsigned char pwm;
      Error lastError;

      State(const State & previous, bool on);
      State(const State & previous, unsigned char level);
      State(const State & previous, Change change);
      State(const State & previous);
      State(const State * previous, const JsonObject & object);
      void serialize(JsonObject & object) const override;

    private:

      void _applyConfig(const bool previousOn, const unsigned char level, const unsigned char pwm);
  };

}
