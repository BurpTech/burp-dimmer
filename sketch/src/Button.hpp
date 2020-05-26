#ifndef Button_hpp
#define Button_hpp

#include <Arduino.h>
#include <functional>

#define BUTTON_ON_RELEASE_PARAM(NAME,ON_RELEASE)\
const Button::Delay __Button_##NAME##_delay = {\
  0,\
  NULL,\
  ON_RELEASE\
};\
const Button::Delay * NAME[] = {&__Button_##NAME##_delay, NULL}

class Button {
  public:
    using f_callback = std::function<void()>;

    struct Delay {
      unsigned long delay;
      f_callback onDelay;
      f_callback onRelease;
    };

    Button(
      int pin,
      unsigned long debounceDelay,
      const Delay ** delays
    ) :
      _pin(pin),
      _debounceDelay(debounceDelay),
      _delays(delays) {
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
            // start long hold timer and
            // reset the current callback
            _delayStart = now;
            _currentDelay = _delays;
          } else {
            // call previous release callback
            f_callback cb = (*_lastDelay)->onRelease;
            if (cb) {
              cb();
            }
          }
        }
      }

      if (_state == LOW) {
        // move to the correct delay
        while (*_currentDelay && (now - _delayStart) > (*_currentDelay)->delay) {
          f_callback cb = (*_currentDelay)->onDelay;
          _lastDelay = _currentDelay;
          _currentDelay++;
          if (cb) {
            cb();
          }
        }
      }
    }

  private:
    int _pin;
    unsigned long _debounceDelay;
    const Delay ** _delays;
    const Delay ** _currentDelay = NULL;
    const Delay ** _lastDelay = NULL;
    unsigned long _delayStart = 0;
    unsigned long _lastDebounceTime = 0;
    int _state = HIGH;
    int _lastState = HIGH;
    bool _notified = false;
};

#endif
