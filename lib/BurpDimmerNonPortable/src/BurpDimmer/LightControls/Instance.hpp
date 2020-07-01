#pragma once

#include <BurpTree/Dispatcher.hpp>
#include <BurpDimmer/Light/State.hpp>
#include <BurpDimmer/Logger.hpp>
#include "../Components/RotaryEncoder.hpp"
#include "../Components/Button.hpp"

namespace BurpDimmer {
  namespace LightControls {

    using namespace Components;

    class Instance {

      public:

        using Factory = Light::Factory;
        using Dispatcher = BurpTree::Dispatcher<Factory>;

        Instance(Dispatcher & dispatcher, RotaryEncoder & rotaryEncoder, Button & button);
        void setup();
        void loop();

      private:

        Dispatcher & _dispatcher;
        RotaryEncoder & _rotaryEncoder;
        Button & _button;
        Logger _logger;

        void _rotaryEncoderChange(int direction);
        void _buttonRelease();

    };

  }
}
