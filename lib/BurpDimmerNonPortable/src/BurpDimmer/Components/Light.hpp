#pragma once

#include <BurpRedux/Subscriber.hpp>
#include <BurpDimmer/Light/State.hpp>

namespace BurpDimmer {
  namespace Components {
    namespace Light {

      using State = BurpDimmer::Light::State::Instance;

      class Instance : public BurpRedux::Subscriber<State> {

        public:

          Instance(int pin);
          void setup(const State * state);
          void onPublish(const State * state) override;

        private:

          int _pin;

      };

    }
  }
}
