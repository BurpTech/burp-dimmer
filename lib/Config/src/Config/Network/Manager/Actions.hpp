#pragma once

#include <ArduinoJson.h>
#include <Redux/Action.hpp>
#include "../../../ActionType.hpp"
#include "./State.hpp"

namespace Config {
  namespace Network {
    namespace Manager {
      namespace Actions {

        class Deserialize: public Redux::Action<ActionType> {
          public:
            const JsonObject & object;
            Deserialize(const JsonObject & object);
        };

        class SetAccessPointTimeout: public Redux::Action<ActionType> {
          public:
            const unsigned long timeout;
            SetAccessPointTimeout(const unsigned long timeout);
        };

        class NextMode: public Redux::Action<ActionType> {
          public:
            NextMode();
        };

        class SetPermMode: public Redux::Action<ActionType> {
          public:
            PermMode mode;
            SetPermMode(PermMode mode);
        };

        class SetTempMode: public Redux::Action<ActionType> {
          public:
            TempMode mode;
            SetTempMode(TempMode mode);
        };

      }
    }
  }
}
