#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        constexpr char testField[] = "test";

        constexpr int defaultTest = 0;

        State::State(const int test) :
          test(test)
        {}

        State::State() :
          State(defaultTest)
        {}

        void State::serialize(const JsonObject & object) const {
          object[testField] = test;
        }

        bool Factory::deserialize(const JsonObject & object) {
          return create([&]() -> const State * {
            if (!object.isNull()) {
              if (object.containsKey(testField)) {
                const JsonVariant v = object[testField];
                if (!v.is<int>()) {
                  return error(Status::invalidTest);
                }
                return ok(new(getAddress()) State(v.as<int>()));
              }
              return error(Status::noTest);
            }
            return error(Status::noObject);
          });
        }

        bool Factory::createDefault() {
          return create([&]() -> const State * {
              return ok(new(getAddress()) State());
          });
        }

        #define C_STR_LABEL "BurpDimmer::Config::Network::AccessPoint"
        #define C_STR_CASE(CODE) BURP_STATUS_C_STR_CASE(C_STR_LABEL, CODE)
        #define C_STR_DEFAULT BURP_STATUS_C_STR_DEFAULT(C_STR_LABEL)
        const char * Status::c_str() const {
          switch (getCode()) {
            C_STR_CASE(ok);
            C_STR_CASE(noObject);
            C_STR_CASE(noTest);
            C_STR_CASE(invalidTest);
            C_STR_DEFAULT;
          }
        }

      }
    }
  }
}
