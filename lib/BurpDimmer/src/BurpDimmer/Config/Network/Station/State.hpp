#pragma once

#include <ArduinoJson.h>
#include <BurpRedux/State/Instance.hpp>
#include <BurpRedux/Creator/Instance.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {
        namespace State {

          constexpr char testField[] = "test";

          enum class Error {
            noError,
            noObject,
            noTest,
            invalidTest
          };

          struct Params {
            Error error;
            int test;
          };

          class Instance : public BurpRedux::State::Instance {

            public:
              
              const int test;

              Instance(const Params & params, const unsigned long uid);
              void serialize(const JsonObject & object) const override;

          };

          using Creator = BurpRedux::Creator::Instance<Instance, Params>;

        }
      }
    }
  }
}
