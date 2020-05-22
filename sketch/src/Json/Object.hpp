#ifndef JsonObject_hpp
#define JsonObject_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Json.hpp"

#define JSON_OBJECT_ARRAY_LENGTH(ARRAY) (sizeof ARRAY / sizeof(Json::Object))

namespace Json {
  class Object {
    public:
      const char * name;
      const f_onObj serialize;
      const f_onObj deserialize;
      Object(
        const char *name,
        const f_onObj serialize,
        const f_onObj deserialize
      )
      : name(name),
        serialize(serialize),
        deserialize(deserialize)
      {}
  };
};

#endif
