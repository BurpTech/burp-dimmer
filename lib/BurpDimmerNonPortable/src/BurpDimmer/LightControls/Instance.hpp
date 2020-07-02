#pragma once

#include <BurpDimmer/Light/State.hpp>
#include <BurpDimmer/Logger.hpp>
#include "../Components/RotaryEncoder.hpp"
#include "../Components/Button.hpp"

namespace BurpDimmer {
  namespace LightControls {

    using namespace Components;
    using namespace std::placeholders;

    template <class Dispatcher>
    class Instance {

      public:

        Instance(Dispatcher & dispatcher, RotaryEncoder & rotaryEncoder, Button & button) :
          _dispatcher(dispatcher),
          _rotaryEncoder(rotaryEncoder),
          _button(button),
          _logger("LightControls")
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

        Dispatcher & _dispatcher;
        RotaryEncoder & _rotaryEncoder;
        Button & _button;
        Logger _logger;

        void _rotaryEncoderChange(int direction) {
          if (direction > 0) {
            _logger.status(_dispatcher.dispatch(&Light::Factory::increaseBrightness));
          } else {
            _logger.status(_dispatcher.dispatch(&Light::Factory::decreaseBrightness));
          }
        }

        void _buttonRelease() {
          _logger.status(_dispatcher.dispatch(&Light::Factory::toggle));
        }

    };

  }
}
