#include <BurpDimmer/Light/Actions.hpp>
#include "Instance.hpp"

namespace BurpDimmer {
  namespace LightControls {

    Instance::Instance(Store & store, RotaryEncoder & rotaryEncoder, Button & button) :
      _store(store),
      _rotaryEncoder(rotaryEncoder),
      _button(button)
    {} 

    void Instance::setup() {
      using namespace std::placeholders;
      _rotaryEncoder.setup(std::bind(&Instance::_rotaryEncoderChange, this, _1));
      _button.setup(std::bind(&Instance::_buttonRelease, this));
    }

    void Instance::loop() {
      _rotaryEncoder.loop();
      _button.loop();
    }

    void Instance::_rotaryEncoderChange(int direction) {
      if (direction > 0) {
        Light::increaseBrightness(_store.getState(), [](const Error error, const Params * params){
            if (Error::noError == error) {
              _store.dispatch(Light::Action(*params));
            }
        });
      } else {
        Light::decreaseBrightness(_store.getState(), [](const Error error, const Params * params){
            if (Error::noError == error) {
              _store.dispatch(Light::Action(*params));
            }
        });
      }
    }

    void Instance::_buttonRelease() {
      toggle(_store.getState(), [](const Error error, const Params * params){
          if (Error::noError == error) {
            _store.dispatch(Light::Action(*params));
          }
      });
    }

  }
}