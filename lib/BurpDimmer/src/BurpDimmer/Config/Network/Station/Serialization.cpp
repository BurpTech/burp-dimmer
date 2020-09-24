#include "Status.hpp"
#include "Serialization.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        constexpr char testField[] = "test";

        Serialization::Serialization() :
          BurpSerialization::Serialization(_root),
          _test({
            Status::ok,
            Status::noTest,
            Status::invalidTest
          }, root.test),
          _root({
            Object::Entry({testField, &_test})
          }, {
            Status::ok,
            Status::noObject,
            Status::invalidObject
          }, root.isNull)
        {}

      }
    }
  }
}
