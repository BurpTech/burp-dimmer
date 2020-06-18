#pragma once

#include <Arduino.h>

namespace BurpDimmer {
  namespace Util {

    class Error {

      public:

        const int code;

        Error(const int code) : 
          code(code) {
        }

    };

  }
}
