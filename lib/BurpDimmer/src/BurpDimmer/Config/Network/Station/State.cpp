#include "Serialization.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        State::State(const int test) :
          test(test)
        {}

        bool State::serialize(const JsonVariant & serialized) const {
          Serialization serialization;
          serialization.root.test.value = test;
          return serialization.serialize(serialized);
        }

      }
    }
  }
}
