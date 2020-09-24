#pragma once

#include <BurpStatus/Status.hpp>

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      class Status : public BurpStatus::Status {
        public:
          enum : BurpStatus::Status::Code {
            ok,
            noObject,
            invalidObject,
            noLevels,
            invalidLevels,
            maxLevels,
            minLevels,
            levelZero,
            levelNotIncreasing,
            levelNotPresent,
            levelWrongType,
            noSaveStateDelay,
            invalidSaveStateDelay,
            noOffLevel,
            invalidOffLevel,
            offLevelOutOfRange
          };
          const char * c_str() const override;
      };

    }
  }
}
