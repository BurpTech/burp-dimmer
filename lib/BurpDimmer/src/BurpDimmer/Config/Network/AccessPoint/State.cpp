#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {
        namespace State {

          Memory memory;

          constexpr int defaultTest = 0;

          Instance::Instance(const Params * params, unsigned long sequenceId) :
            test(params ? params->test : defaultTest),
            sequenceId(sequenceId)
          {}

          void Instance::serialize(JsonObject & object) const {
            object[testField] = test;
          }

          unsigned long Instance::getUid() const {
            return sequenceId;
          }

        }
      }
    }
  }
}
