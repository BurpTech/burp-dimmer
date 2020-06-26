#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {
        namespace State {

          constexpr int defaultTest = 0;

          Instance::Instance(const Params * params, const unsigned long uid) :
            BurpRedux::State::Instance(uid),
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
