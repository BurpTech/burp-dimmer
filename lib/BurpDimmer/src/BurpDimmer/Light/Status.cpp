#include "Status.hpp"

namespace BurpDimmer {
  namespace Light {

    #define C_STR_LABEL "BurpDimmer::Light"
    #define C_STR_CASE(CODE) BURP_STATUS_C_STR_CASE(C_STR_LABEL, CODE)
    #define C_STR_DEFAULT BURP_STATUS_C_STR_DEFAULT(C_STR_LABEL)
    const char * Status::c_str() const {
      switch (getCode()) {
        C_STR_CASE(ok);
        C_STR_CASE(noObject);
        C_STR_CASE(invalidObject);
        C_STR_CASE(maxLevels);
        C_STR_CASE(outOfRange);
        C_STR_CASE(noOn);
        C_STR_CASE(invalidOn);
        C_STR_CASE(noLevel);
        C_STR_CASE(invalidLevel);
        C_STR_CASE(noPwm);
        C_STR_CASE(invalidPwm);
        C_STR_CASE(maxBrightness);
        C_STR_CASE(minBrightness);
        C_STR_DEFAULT;
      }
    }

  }
}
