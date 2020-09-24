#pragma once

#include <BurpTree/Factory.hpp>
#include "State.hpp"
#include "Status.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      class Factory : public BurpTree::Factory<State, Status> {

        public:

          bool deserialize(const JsonVariant & serialized) override ;
          bool createDefault() override;

      };

    }
  }
}
