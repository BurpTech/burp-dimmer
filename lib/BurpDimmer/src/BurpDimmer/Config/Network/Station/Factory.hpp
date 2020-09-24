#pragma once

#include <BurpTree/Factory.hpp>
#include "Status.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        class Factory : public BurpTree::Factory<State, Status> {

          public:

            bool deserialize(const JsonVariant & serialized) override ;
            bool createDefault() override;

        };

      }
    }
  }
}
