#pragma once

#include <BurpSerialization/Serialization.hpp>
#include <BurpSerialization/Scalar.hpp>
#include <BurpSerialization/Object.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Station {

        class Serialization : public BurpSerialization::Serialization {

          private:

              using TestScalar = BurpSerialization::Scalar<uint16_t>;

          public:

              struct {
                  bool isNull = false;
                  TestScalar::Value test;
              } root;

              Serialization();

          private:

              using Object = BurpSerialization::Object<1>;

              const TestScalar _test;
              const Object _root;

        };

      }
    }
  }
}
