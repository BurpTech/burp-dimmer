#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {
        namespace State {

          Memory memory;

          constexpr int defaultTest = 0;

          Instance::Instance(const Params * params) :
            test(params ? params->test : defaultTest)
          {}

          void Instance::serialize(JsonObject & object) const {
            object[testField] = test;
          }

        }
      }
    }
  }
}
