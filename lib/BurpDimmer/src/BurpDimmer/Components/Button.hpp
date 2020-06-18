#include "Button.hpp"

#include <Arduino.h>

namespace BurpDimmer {
  namespace Components {

    Button::Button(
      int pin,
      unsigned long debounceDelay,
      unsigned long delay,
      f_callback onPress,
      f_callback onRelease
    ) :
      _pin(pin),
      _debounceDelay(debounceDelay),
      _longPresses(_ppSingle),
      _single({delay, onPress, onRelease}) {
    }

    Button::Button(
      int pin,
      unsigned long debounceDelay,
      f_callback onPress,
      f_callback onRelease
    ) :
      Button(pin, debounceDelay, 0, onPress, onRelease) {
    }

    Button::Button(
      int pin,
      unsigned long debounceDelay,
      unsigned long delay,
      f_callback onRelease
    ) :
      Button(pin, debounceDelay, delay, nullptr, onRelease) {
    }

    Button::Button(
      int pin,
      unsigned long debounceDelay,
      f_callback onRelease
    ) :
      Button(pin, debounceDelay, nullptr, onRelease) {
    }

    Button::Button(
      int pin,
      unsigned long debounceDelay,
      const LongPress ** longPresses
    ) :
      _pin(pin),
      _debounceDelay(debounceDelay),
      _longPresses(longPresses) {
    }

    void Button::setup() {
      pinMode(_pin, INPUT_PULLUP);
    }

    void Button::loop() {
      int reading = digitalRead(_pin);
      if (reading != _lastState) {
        _lastDebounceTime = millis();
      }
      _lastState = reading;

      unsigned long now = millis();
      if ((now - _lastDebounceTime) > _debounceDelay) {
        if (reading != _state) {
          _state = reading;
          if (_state == LOW) {
            // start long press timer and
            // reset the current callback
            _start = now;
            _currentLongPress = _longPresses;
          } else {
            // call previous release callback
            f_callback cb = (*_lastLongPress)->onRelease;
            if (cb) {
              cb();
            }
          }
        }
      }

      if (_state == LOW) {
        // move to the correct long press
        while (*_currentLongPress && (now - _start) > (*_currentLongPress)->delay) {
          _start += (*_currentLongPress)->delay;
          f_callback cb = (*_currentLongPress)->onPress;
          _lastLongPress = _currentLongPress;
          _currentLongPress++;
          if (cb) {
            cb();
          }
        }
      }
    }

  }
}
