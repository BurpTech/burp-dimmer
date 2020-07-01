#pragma once

#include <BurpTree/Subscriber.hpp>
#include <BurpDimmer/Light/State.hpp>

namespace BurpDimmer {
  namespace Components {
    namespace Light {

      class Instance : public BurpTree::Subscriber {

        public:

          using State = BurpDimmer::Light::State;

          Instance(int pin);
          void setup(const BurpTree::State * state) override;
          void onPublish(const BurpTree::State * state) override;

        private:

          int _pin;

      };

    }
  }
}
