#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {
        namespace State {

          constexpr int defaultTest = 0;

          Instance::Instance(const Params & params, const unsigned long uid) :
            BurpRedux::State::Instance(uid),
            test(params.error == Error::noError ? params.test : defaultTest)
          {}

          void Instance::serialize(const JsonObject & object) const {
            object[testField] = test;
          }

        }
      }
    }
  }
}
