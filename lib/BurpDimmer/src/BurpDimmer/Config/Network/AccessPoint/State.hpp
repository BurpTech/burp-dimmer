#pragma once

#include <ArduinoJson.h>
#include <BurpRedux/State.hpp>
#include "../../../Memory/Pair.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {
        namespace State {

          constexpr char testField[] = "test";

          struct Params {
            const int test;
          };

          class Instance : public BurpRedux::State {

            public:
              
              const int test;

              Instance(const Params * params, unsigned long sequenceId);
              void serialize(JsonObject & object) const;
              unsigned long getUid() const override;

            private:

              unsigned long sequenceId;

          };

          using Memory = Memory::Pair<Instance, Params>;
          extern Memory memory;

        }
      }
    }
  }
}
