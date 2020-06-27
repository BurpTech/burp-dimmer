#pragma once

#include <BurpDimmer/Light/Store.hpp>
#include "../Components/RotaryEncoder.hpp"
#include "../Components/Button.hpp"

namespace BurpDimmer {
  namespace LightControls {

    using Store = Light::Store::Interface;
    using namespace Components;

    class Instance {
      public:

        Instance(Store & store, RotaryEncoder & rotaryEncoder, Button & button);
        void setup();
        void loop();

      private:

        Store & _store;
        RotaryEncoder & _rotaryEncoder;
        Button & _button;

        void _rotaryEncoderChange(int direction);
        void _buttonRelease();

    };

  }
}
