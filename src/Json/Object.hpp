#ifndef JsonObject_hpp
#define JsonObject_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Json.hpp"

namespace Json {
  class Object {
    public:
      const char * name;

      Object(const char * name) :
        name(name) {
      }

      virtual void serialize(JsonObject & object) = 0;
      virtual void deserialize(JsonObject & object) = 0;
  };
};

#endif
