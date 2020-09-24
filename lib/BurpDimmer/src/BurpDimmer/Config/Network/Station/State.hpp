#pragma once

#include <BurpTree/State.hpp>
#include <BurpTree/Factory.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        class State : public BurpTree::State {

          public:

            const uint16_t test;

            State(
                const int test
            );
            bool serialize(const JsonVariant & serialized) const override;

        };

      }
    }
  }
}
