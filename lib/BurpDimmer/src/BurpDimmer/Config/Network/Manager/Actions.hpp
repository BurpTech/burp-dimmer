#pragma once

#include <ArduinoJson.h>
#include <functional>
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        enum class Error {
          noError,
          noObject,
          noMode,
          noAccessPointTimeout,
          invalidMode,
          invalidAccessPointTimeout,
          unknownMode
        };

        using f_onParams = std::function<void(const Error error, const Params * params)>;
        void deserialize(const JsonObject & object, f_onParams onParams);
        void nextPermMode(const State * previous, f_onParams onParams);
        void startTempAccessPoint(const State * previous, f_onParams onParams);
        void startWpsConfig(const State * previous, f_onParams onParams);
        void stopTempMode(const State * previous, f_onParams onParams);
        void setNormalMode(const State * previous, f_onParams onParams);

      }
    }
  }
}
