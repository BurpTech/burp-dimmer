#include <Arduino.h>
#include "Light.hpp"


namespace BurpDimmer {
  namespace Components {
    namespace Light {

      Instance::Instance(const BurpLogger::Logger * logger, const int pin) :
        _logger(logger),
        _pin(pin)
      {}

      void Instance::setup(const State * initial) {
        pinMode(_pin, OUTPUT);
        update(initial);
      }

      void Instance::update(const State * next) {
        if (next->on) {
          _logger->info("pwm: %u", next->pwm);
          analogWrite(_pin, next->pwm);
        } else {
          _logger->info("off");
          digitalWrite(_pin, LOW);
        }
      }

    }
  }
}
