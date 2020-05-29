#ifndef Network_Mode_Off_hpp
#define Network_Mode_Off_hpp

#include <Arduino.h>

#include "../../Debug.hpp"

#include "Mode.hpp"

namespace Network {
  namespace Mode {
    class Off : public Mode {
      public:
        Off(const char * name, const char * displayName) :
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
