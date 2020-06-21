#include <BurpDimmer/Light/Store.hpp>
#include <BurpDimmer/Config/Light/Selector.hpp>
#include <BurpDimmer/Light/Actions.hpp>
#include "defines.hpp"
#include "LightControls.hpp"

namespace BurpDimmer {
  namespace LightControls {

    using namespace Config::Light;
    using namespace Light;
    using namespace Light::State;

    ICACHE_RAM_ATTR void rotaryEncoderInterruptDispatch();
    void rotaryEncoderChange(int direction);
    void buttonRelease();

    Components::RotaryEncoder rotaryEncoder(
      BURP_DIMMER_LIGHT_ROTARY_ENCODER_PIN_1,
      BURP_DIMMER_LIGHT_ROTARY_ENCODER_PIN_2,
      rotaryEncoderInterruptDispatch,
      rotaryEncoderChange
    );

    Components::Button button(
      BURP_DIMMER_LIGHT_BUTTON_PIN,
      BURP_DIMMER_DEBOUNCE_DELAY,
      buttonRelease
    );

    void setup() {
      rotaryEncoder.setup();
      button.setup();
    }

    void loop() {
      rotaryEncoder.loop();
      button.loop();
    }

    void rotaryEncoderInterruptDispatch() {
      rotaryEncoder.interrupt();
    }

    void rotaryEncoderChange(int direction) {
      if (direction > 0) {
        increaseBrightness(store->getState(), selector->getState(), [](const Error error, const Params * params){
            if (Error::noError == error) {
              store->dispatch(Action(ActionType::SET_STATE, params));
            }
        });
      } else {
        decreaseBrightness(store->getState(), selector->getState(), [](const Error error, const Params * params){
            if (Error::noError == error) {
              store->dispatch(Action(ActionType::SET_STATE, params));
            }
        });
      }
    }

    void buttonRelease() {
      toggle(store->getState(), selector->getState(), [](const Error error, const Params * params){
          if (Error::noError == error) {
            store->dispatch(Action(ActionType::SET_STATE, params));
          }
      });
    }

  }
}
