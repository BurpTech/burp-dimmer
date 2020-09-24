#include "Status.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      #define C_STR_LABEL "BurpDimmer::Config::Light"
      #define C_STR_CASE(CODE) BURP_STATUS_C_STR_CASE(C_STR_LABEL, CODE)
      #define C_STR_DEFAULT BURP_STATUS_C_STR_DEFAULT(C_STR_LABEL)
      const char * Status::c_str() const {
        switch (getCode()) {
          C_STR_CASE(ok);
          C_STR_CASE(noObject);
          C_STR_CASE(invalidObject);
          C_STR_CASE(noLevels);
          C_STR_CASE(invalidLevels);
          C_STR_CASE(maxLevels);
          C_STR_CASE(minLevels);
          C_STR_CASE(levelZero);
          C_STR_CASE(levelNotIncreasing);
          C_STR_CASE(levelNotPresent);
          C_STR_CASE(levelWrongType);
          C_STR_CASE(noSaveStateDelay);
          C_STR_CASE(invalidSaveStateDelay);
          C_STR_CASE(noOffLevel);
          C_STR_CASE(invalidOffLevel);
          C_STR_CASE(offLevelOutOfRange);
          C_STR_DEFAULT;
        }
      }

    }
  }
}
