#pragma once

#include <BurpRedux/Subscriber/Interface.hpp>
#include <BurpDimmer/Light/State.hpp>

namespace BurpDimmer {
  namespace Components {
    namespace Light {

      using State = BurpDimmer::Light::State::Instance;

      class Instance : public BurpRedux::Subscriber::Interface<State> {

        public:

          Instance(int pin);
          void setup(const State * state) override;
          void onPublish(const State * state) override;

        private:

          int _pin;

      };

    }
  }
}
