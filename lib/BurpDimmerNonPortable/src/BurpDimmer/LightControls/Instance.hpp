#pragma once

#include <BurpLogger.hpp>
#include <BurpDimmer/Light/State.hpp>
#include "../Components/RotaryEncoder.hpp"
#include "../Components/Button.hpp"

namespace BurpDimmer {
  namespace LightControls {

    using namespace Components;
    using namespace std::placeholders;

    template <class Updater>
    class Instance {

      public:

        Instance(const BurpLogger::Logger * logger, Updater & updater, RotaryEncoder & rotaryEncoder, Button & button) :
          _updater(updater),
          _rotaryEncoder(rotaryEncoder),
          _button(button),
          _logger(logger)
        {} 

        void setup() {
          _rotaryEncoder.setup(std::bind(&Instance::_rotaryEncoderChange, this, _1));
          _button.setup(std::bind(&Instance::_buttonRelease, this));
        }

        void loop() {
          _rotaryEncoder.loop();
          _button.loop();
        }

      private:

        Updater & _updater;
        RotaryEncoder & _rotaryEncoder;
        Button & _button;
        const BurpLogger::Logger * _logger;

        void _rotaryEncoderChange(int direction) {
          if (direction > 0) {
            _logger.status(_updater.update(&Light::Factory::increaseBrightness));
          } else {
            _logger.status(_updater.update(&Light::Factory::decreaseBrightness));
          }
        }

        void _buttonRelease() {
          _logger.status(_updater.update(&Light::Factory::toggle));
        }

    };

  }
}
