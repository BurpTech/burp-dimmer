#ifndef Error_hpp
#define Error_hpp

#include <Arduino.h>

class Error {
  public:
    const int code;
    Error(const int code) : 
      code(code) {
    }
};

#endif
