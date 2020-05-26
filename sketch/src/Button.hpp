#ifndef Button_hpp
#define Button_hpp

#include <Arduino.h>
#include <functional>

class Button {
  public:
    using f_callback = std::function<void()>;

    struct LongPress {
      unsigned long delay;
      f_callback onPress;
      f_callback onRelease;
    };

    Button(
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

    Button(
      int pin,
      unsigned long debounceDelay,
      f_callback onPress,
      f_callback onRelease
    ) :
      Button(pin, debounceDelay, 0, onPress, onRelease) {
    }

    Button(
      int pin,
      unsigned long debounceDelay,
      unsigned long delay,
      f_callback onRelease
    ) :
      Button(pin, debounceDelay, delay, NULL, onRelease) {
    }

    Button(
      int pin,
      unsigned long debounceDelay,
      f_callback onRelease
    ) :
      Button(pin, debounceDelay, NULL, onRelease) {
    }

    Button(
      int pin,
      unsigned long debounceDelay,
      const LongPress ** longPresses
    ) :
      _pin(pin),
      _debounceDelay(debounceDelay),
      _longPresses(longPresses) {
    }

    void setup() {
      pinMode(_pin, INPUT_PULLUP);
    }

    void loop() {
      bool notify = false;
      bool longNotify = false;
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

  private:
    int _pin;
    unsigned long _debounceDelay;
    const LongPress ** _longPresses;
    const LongPress ** _currentLongPress = NULL;
    const LongPress ** _lastLongPress = NULL;
    unsigned long _start = 0;
    unsigned long _lastDebounceTime = 0;
    int _state = HIGH;
    int _lastState = HIGH;
    bool _notified = false;
    LongPress _single;
    const LongPress * _ppSingle[2] = {
      &_single,
      NULL
    };
};

#endif
