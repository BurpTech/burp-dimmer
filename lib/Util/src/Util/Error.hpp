#ifndef Util_Error_hpp
#define Util_Error_hpp

#include <Arduino.h>

namespace Util {

  class Error {

    public:

      const int code;

      Error(const int code) : 
        code(code) {
      }

  };

}

#endif
