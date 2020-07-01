#include "State.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        constexpr char testField[] = "test";

        constexpr int defaultTest = 0;

        State::State(
            const Uid uid,
            const int test
        ) :
          BurpTree::State(uid),
          test(test)
        {}

        State::State(const Uid uid) :
          State(uid, defaultTest)
        {}

        void State::serialize(const JsonObject & object) const {
          object[testField] = test;
        }

        const BurpTree::State * Factory::deserialize(const JsonObject & object) {
          return create([&]() -> const State * {
            if (!object.isNull()) {
              if (object.containsKey(testField)) {
                const JsonVariant v = object[testField];
                if (!v.is<int>()) {
                  return fail(Status::invalidTest);
                }
                return new(getAddress()) State(getUid(), v.as<int>());
              }
              return fail(Status::noTest);
            }
            return fail(Status::noObject);
          });
        }

        const State * Factory::_default() {
          return new(getAddress()) State(getUid());
        }

        #define C_STR_LABEL "BurpDimmer::Config::Network::AccessPoint"
        #define C_STR_CASE(CODE) BURP_TREE_C_STR_CASE(C_STR_LABEL, CODE)
        #define C_STR_DEFAULT BURP_TREE_C_STR_DEFAULT(C_STR_LABEL)
        const char * Status::c_str() const {
          switch (getCode()) {
            C_STR_CASE(noError);
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
