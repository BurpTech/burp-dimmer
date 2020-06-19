#pragma once

#include "stddef.h"

namespace BurpDimmer {
  namespace Components {

    class Blinker {

      public:

        Blinker(int pin, int on);
        void setup();
        void blink(size_t count, unsigned long delay);
        void blink(size_t count, unsigned long on, unsigned long off);

      private:

        int _pin;
        int _on;

    };

  }
}
