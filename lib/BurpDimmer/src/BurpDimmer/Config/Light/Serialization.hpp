#pragma once

#include <BurpSerialization/Serialization.hpp>
#include <BurpSerialization/PWMLevels.hpp>
#include <BurpSerialization/Scalar.hpp>
#include <BurpSerialization/Object.hpp>
#include "Types.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      class Serialization : public BurpSerialization::Serialization {

        public:

            struct {
                bool isNull = false;
                BurpSerialization::PWMLevels::Value levels;
                BurpSerialization::Scalar<Delay>::Value saveStateDelay;
                BurpSerialization::Scalar<LevelIndex>::Value offLevel;
            } root;

            Serialization();

        private:

            using Object = BurpSerialization::Object<3>;

            const BurpSerialization::PWMLevels _levels;
            const BurpSerialization::Scalar<Delay> _saveStateDelay;
            const BurpSerialization::Scalar<LevelIndex> _offLevel;
            const Object _root;

      };

    }
  }
}
