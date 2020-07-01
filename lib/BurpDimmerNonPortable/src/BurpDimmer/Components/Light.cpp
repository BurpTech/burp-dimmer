#include <Arduino.h>
#include <BurpDebug.hpp>
#include "Light.hpp"


namespace BurpDimmer {
  namespace Components {
    namespace Light {

      Instance::Instance(int pin) :
        _pin(pin)
      {}

      void Instance::setup(const BurpTree::State * state) {
        pinMode(_pin, OUTPUT);
        onPublish(state);
      }

      void Instance::onPublish(const BurpTree::State * state) {
        const State * s = state->as<State>();
        if (s->on) {
          analogWrite(_pin, s->pwm);
        } else {
          digitalWrite(_pin, LOW);
        }
      }

    }
  }
}
