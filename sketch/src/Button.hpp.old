#ifndef Button_hpp
#define Button_hpp

#include "Debug.hpp"

#define _BUTTON_DEBOUNCE_DELAY 50

class Button {
  using f_onRelease = std::function<void()>;

  int _pin;
  int _pinState;
  int _lastPinState;
  unsigned long _lastDebounceTime;
  f_onRelease _onRelease;

  public:
    Button(int pin, f_onRelease onRelease) :
      _pin(pin),
      _onRelease(onRelease),
      _lastDebounceTime(0) {
    }

    void setup() {
      pinMode(_pin, INPUT_PULLUP);
      _pinState = digitalRead(_pin);
      _lastPinState = _pinState;
    }

    void loop() {
      int pinState = digitalRead(_pin);
      if (_lastPinState != pinState) {
        _lastDebounceTime = millis();
        _lastPinState = pinState;
      }

      if (_pinState != pinState) {
        if ((millis() - _lastDebounceTime) > _BUTTON_DEBOUNCE_DELAY) {
          _pinState = pinState;
          if (_pinState == HIGH) {
            _onRelease();
          }
        }
      }
    }
};

#endif
