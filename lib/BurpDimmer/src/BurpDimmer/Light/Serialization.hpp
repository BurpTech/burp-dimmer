#pragma once

#include <BurpSerialization/Serialization.hpp>
#include <BurpSerialization/Scalar.hpp>
#include <BurpSerialization/Object.hpp>
#include "Types.hpp"

namespace BurpDimmer {
  namespace Light {

    class Serialization : public BurpSerialization::Serialization {

      public:

          struct {
              bool isNull = false;
              BurpSerialization::Scalar<bool>::Value on;
              BurpSerialization::Scalar<LevelIndex>::Value level;
              BurpSerialization::Scalar<Level>::Value pwm;
          } root;

          Serialization();

      private:

          using Object = BurpSerialization::Object<3>;

          const BurpSerialization::Scalar<bool> _on;
          const BurpSerialization::Scalar<LevelIndex> _level;
          const BurpSerialization::Scalar<Level> _pwm;
          const Object _root;

    };

  }
}
