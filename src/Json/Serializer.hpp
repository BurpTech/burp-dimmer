#ifndef Json_Serializer_hpp
#define Json_Serializer_hpp

#include <ArduinoJson.h>

namespace Json {
  class Serializer {
    public:
      virtual void serialize(JsonObject & object) const = 0;
  };
};

#endif
