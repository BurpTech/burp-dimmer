#pragma once

#include <BurpLogger.hpp>
#include <BurpTree/Subscriber.hpp>
#include <BurpDimmer/Light/State.hpp>

namespace BurpDimmer {
  namespace Components {
    namespace Light {

      class Instance : public BurpTree::Subscriber<BurpDimmer::Light::State> {

        public:

          using State = BurpDimmer::Light::State;

          Instance(const BurpLogger::Logger * logger, const int pin);
          void setup(const State * state) override;
          void update(const State * state) override;

        private:

          const BurpLogger::Logger * _logger;
          const int _pin;

      };

    }
  }
}
