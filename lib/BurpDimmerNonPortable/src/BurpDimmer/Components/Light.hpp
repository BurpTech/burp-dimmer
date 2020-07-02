#pragma once

#include <BurpTree/Subscriber.hpp>
#include <BurpDimmer/Light/State.hpp>

namespace BurpDimmer {
  namespace Components {
    namespace Light {

      class Instance : public BurpTree::Subscriber<BurpDimmer::Light::State> {

        public:

          using State = BurpDimmer::Light::State;

          Instance(int pin);
          void setup(const State * state) override;
          void update(const State * state) override;

        private:

          int _pin;

      };

    }
  }
}
