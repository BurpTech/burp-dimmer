#ifndef JsonObject_hpp
#define JsonObject_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Json.hpp"

namespace Json {
  class Object {
    public:
      const char * name;

      Object(const char *name) :
        name(name) {
      }

      virtual void serialize(JsonObject * pObj) = 0;
      virtual void deserialize(JsonObject * pObj) = 0;
  };
};

#endif
