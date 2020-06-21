#pragma once

#include <ArduinoJson.h>
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

          class Instance {

            public:
              
              const int test;

              Instance(const Params * params);
              void serialize(JsonObject & object) const;

          };

          using Memory = Memory::Pair<Instance, Params>;
          extern Memory memory;

        }
      }
    }
  }
}
