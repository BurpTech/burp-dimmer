#include "Instance.hpp"

namespace BurpDimmer {
  namespace LightControls {

    using namespace std::placeholders;
    using Factory = Light::Factory;
    using Status = BurpTree::Status;

    Instance::Instance(Dispatcher & dispatcher, RotaryEncoder & rotaryEncoder, Button & button) :
      _dispatcher(dispatcher),
      _rotaryEncoder(rotaryEncoder),
      _button(button),
      _logger("LightControls")
    {} 

    void Instance::setup() {
      _rotaryEncoder.setup(std::bind(&Instance::_rotaryEncoderChange, this, _1));
      _button.setup(std::bind(&Instance::_buttonRelease, this));
    }

    void Instance::loop() {
      _rotaryEncoder.loop();
      _button.loop();
    }

    void Instance::_rotaryEncoderChange(int direction) {
      if (direction > 0) {
        _logger.status(_dispatcher.dispatch(&Factory::increaseBrightness));
      } else {
        _logger.status(_dispatcher.dispatch(&Factory::decreaseBrightness));
      }
    }

    void Instance::_buttonRelease() {
      _logger.status(_dispatcher.dispatch(&Factory::toggle));
    }

  }
}
