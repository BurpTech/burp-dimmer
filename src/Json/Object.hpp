#ifndef Json_Object_hpp
#define Json_Object_hpp

#include <ArduinoJson.h>

namespace Json {
  class Object {
    public:
      virtual void serialize(JsonObject & object) = 0;
      virtual void deserialize(JsonObject & object) = 0;
  };
};

#endif
