#pragma once

#include <functional>

#define ROTARY_ENCODER_LEFT (-1)
#define ROTARY_ENCODER_RIGHT 1
#define ROTARY_ENCODER_BUFFER_SIZE 50

namespace BurpDimmer {
  namespace Components {

    class RotaryEncoder {

      public:

        using f_onChange = std::function<void(int direction)>;

        // can't use <functional> stuff with attachInterrupt
        // which means the interrupt callback cannot be a
        // member function
        using f_interruptDispatch = void(*)();

        RotaryEncoder(int pinA, int pinB, f_interruptDispatch interruptDispatch, f_onChange onChange);
        void setup();
        void loop();
        ICACHE_RAM_ATTR void interrupt();

      private:

        enum class State {
          UNCHANGED,
          A_RISING,
          A_FALLING,
          B_RISING,
          B_FALLING
        };

        int _pinA;
        int _pinB;
        volatile int _pinAState;
        volatile int _pinBState;
        volatile State _buffer[ROTARY_ENCODER_BUFFER_SIZE];
        volatile unsigned int _writePos;
        unsigned int _readPos;
        State _state;
        f_interruptDispatch _interruptDispatch;
        f_onChange _onChange;

    };

  }
}
