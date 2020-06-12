#pragma once

#include <array>
#include <ArduinoJson.h>
#include <Json/Serializer.hpp>

namespace Config {
  namespace Light {

    constexpr unsigned char maxLevels = 50;

    enum class Error {
      noError,
      levelsNotProvided,
      notAnArray,
      minLevels,
      maxLevels,
      invalidLevels
    };

    class State : public Json::Serializer {
      public:

        std::array<unsigned char, maxLevels> levels;
        unsigned char levelCount;
        Error lastError;

        State(const State * previous, const JsonObject & object);
        void serialize(JsonObject & object) const override;

    };

  }
}
