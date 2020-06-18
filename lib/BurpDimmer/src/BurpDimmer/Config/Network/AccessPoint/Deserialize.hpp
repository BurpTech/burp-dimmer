#pragma once

#include <ArduinoJson.h>
#include <functional>
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        enum class Error {
          noError,
          noObject,
          noTest,
          invalidTest
        };

        using f_onParams = std::function<void(const Error error, const Params * params)>;
        void deserialize(const JsonObject & object, f_onParams onParams);

        using f_onState = std::function<void(const State * state)>;
        void deserialize(const JsonObject & object, f_onState onState);

      }
    }
  }
}
