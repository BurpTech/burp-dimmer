#include <Arduino.h>
#include <BurpDimmer/Util/Debug.hpp>
#include <BurpDimmer/Light.hpp>
#include "Light.hpp"


namespace BurpDimmer {
  namespace Components {

    using State = BurpDimmer::Light::State;

    Light::Light(int pin, const Light::Store & store) :
      _pin(pin),
      _store(store)
    {}

    void Light::setup() {
      pinMode(_pin, OUTPUT);
      notify();
    }

    void Light::notify() {
      const State * state = _store.getState();
      if (state->on) {
        analogWrite(_pin, state->pwm);
      } else {
        digitalWrite(_pin, LOW);
      }
    }

  }
}
