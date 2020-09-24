#pragma once

#include <BurpStatus/Status.hpp>

namespace BurpDimmer {
  namespace Light {

    class Status : public BurpStatus::Status {
      public:
        enum : BurpStatus::Status::Code {
          ok,
          noObject,
          invalidObject,
          maxLevels,
          outOfRange,
          noOn,
          invalidOn,
          noLevel,
          invalidLevel,
          noPwm,
          invalidPwm,
          maxBrightness,
          minBrightness
        };
        const char * c_str() const override;
    };

  }
}
