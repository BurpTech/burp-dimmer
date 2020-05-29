#ifndef Network_Mode_Normal_hpp
#define Network_Mode_Normal_hpp

#include <Arduino.h>

#include "../../Debug.hpp"

#include "Mode.hpp"

namespace Network {
  namespace Mode {
    class Normal : public Mode {
      public:
        Normal(const char * name, const char * displayName) :
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
