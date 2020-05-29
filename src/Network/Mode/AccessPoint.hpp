#ifndef Network_Mode_AccessPoint_hpp
#define Network_Mode_AccessPoint_hpp

#include <Arduino.h>

#include "../../Debug.hpp"

#include "Mode.hpp"

namespace Network {
  namespace Mode {
    class AccessPoint : public Mode {
      public:
        AccessPoint(const char * name, const char * displayName) :
          Mode(name, displayName) {
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
    };
  }
}

#endif
