#include <Arduino.h>
#include <BurpDimmer/Util/Debug.hpp>
#include <BurpDimmer/Light.hpp>
#include "Light.hpp"


namespace BurpDimmer {
  namespace Components {

    using namespace BurpDimmer::Light;

    Light::Light(int pin) :
      _pin(pin)
    {}

    void Light::setup() {
      pinMode(_pin, OUTPUT);
      notify();
    }

    void Light::notify() {
      const State * state = store.getState();
      if (state->on) {
        analogWrite(_pin, state->pwm);
      } else {
        digitalWrite(_pin, LOW);
      }
    }

  }
}
