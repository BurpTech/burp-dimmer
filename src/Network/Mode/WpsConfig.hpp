#ifndef Network_Mode_WpsConfig_hpp
#define Network_Mode_WpsConfig_hpp

#include <Arduino.h>

#include "../../Debug.hpp"

#include "Mode.hpp"

namespace Network {
  namespace Mode {
    class WpsConfig : public Mode {
      public:
        WpsConfig(const char * name, const char * displayName, const int next) :
          Mode(name, displayName),
          _next(next) {
        }

        void start(Mode::f_callback started, Mode::f_done done) {
          DEBUG_PRINT("TODO");
        }

        void stop(Mode::f_callback started) {
          DEBUG_PRINT("TODO");
        }

        void setup() {
          DEBUG_PRINT("TODO");
        }

        void loop() {
        }

      private:
        const int _next;
    };
  }
}

#endif
