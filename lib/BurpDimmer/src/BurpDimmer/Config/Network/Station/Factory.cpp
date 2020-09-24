#include "Serialization.hpp"
#include "Factory.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        constexpr int defaultTest = 0;

        bool Factory::deserialize(const JsonVariant & serialized) {
          return create([&]() -> const State * {
            Serialization serialization;
            auto code = serialization.deserialize(serialized);
            if (code == Status::ok) {
              return ok(new(getAddress()) State(
                serialization.root.test.value
              ));
            }
            return error(code);
          });
        }

        bool Factory::createDefault() {
          return create([&]() -> const State * {
              return ok(new(getAddress()) State(
                defaultTest
              ));
          });
        }

      }
    }
  }
}
