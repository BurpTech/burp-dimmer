#pragma once

#include <Arduino.h>
#include <functional>

namespace BurpDimmer {
  namespace Components {

    class Button {
      public:
        using f_callback = std::function<void()>;

        struct LongPress {
          unsigned long delay;
          f_callback onPress;
          f_callback onRelease;
        };

        Button(int pin, unsigned long debounceDelay);
        void setup();
        void setup(
          const LongPress ** longPresses
        );
        void setup(
          f_callback onRelease
        );
        void setup(
          unsigned long delay,
          f_callback onRelease
        );
        void setup(
          f_callback onPress,
          f_callback onRelease
        );
        void setup(
          unsigned long delay,
          f_callback onPress,
          f_callback onRelease
        );
        void loop();

      private:
        int _pin;
        unsigned long _debounceDelay;
        const LongPress ** _longPresses;
        const LongPress ** _currentLongPress = nullptr;
        const LongPress ** _lastLongPress = nullptr;
        unsigned long _start = 0;
        unsigned long _lastDebounceTime = 0;
        int _state = HIGH;
        int _lastState = HIGH;
        bool _notified = false;
        LongPress _single;
        const LongPress * _ppSingle[2] = {
          &_single,
          nullptr
        };
    };

  }
}
