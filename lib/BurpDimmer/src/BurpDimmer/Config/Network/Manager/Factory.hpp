#pragma once

#include <BurpTree/Factory.hpp>
#include "Status.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        class Factory : public BurpTree::Factory<State, Status> {

          public:

            bool createDefault() override;
            bool deserialize(const JsonVariant & serialized) override ;
            bool nextPermMode();
            bool startTempAccessPoint();
            bool startWpsConfig();
            bool stopTempMode();
            bool setNormalMode();

        };

      }
    }
  }
}
