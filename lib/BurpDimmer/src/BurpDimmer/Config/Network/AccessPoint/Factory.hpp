#pragma once

#include <BurpTree/Factory.hpp>
#include "Status.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        class Factory : public BurpTree::Factory<State, Status> {

          public:

            void setDefaults(const char * defaultSsid, const char * defaultPassphrase);
            bool deserialize(const JsonVariant & serialized) override ;
            bool createDefault() override;

          private:

            const char * _defaultSsid;
            const char * _defaultPassphrase;

        };

      }
    }
  }
}
