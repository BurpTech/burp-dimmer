#include <Arduino.h>
#include "Button.hpp"

namespace BurpDimmer {
  namespace Components {

    Button::Button(int pin, unsigned long debounceDelay) :
      _pin(pin),
      _debounceDelay(debounceDelay)
    {}

    void Button::setup(
      unsigned long delay,
      f_callback onPress,
      f_callback onRelease
    ) {
      setup();
      _longPresses = _ppSingle;
      _single = {
        delay,
        onPress,
        onRelease
      };
    }

    void Button::setup(
      f_callback onPress,
      f_callback onRelease
    ) {
      setup(0, onPress, onRelease);
    }

    void Button::setup(
      unsigned long delay,
      f_callback onRelease
    ) {
      setup(delay, nullptr, onRelease);
    }

    void Button::setup(
      f_callback onRelease
    ) {
      setup(nullptr, onRelease);
    }

    void Button::setup(
      const LongPress ** longPresses
    ) {
      setup();
      _longPresses = longPresses;
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
