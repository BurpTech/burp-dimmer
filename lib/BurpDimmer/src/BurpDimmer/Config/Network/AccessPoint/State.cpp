#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        Memory::Pair<State, Params> memory;

        constexpr int defaultTest = 0;

        State::State(const Params * params) :
          test(params ? params->test : defaultTest)
        {}

        void State::serialize(JsonObject & object) const {
          object[testField] = test;
        }

      }
    }
  }
}
