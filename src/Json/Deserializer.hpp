#ifndef Json_Deserializer_hpp
#define Json_Deserializer_hpp

#include <ArduinoJson.h>

namespace Json {
  class Deserializer {
    public:
      virtual void deserialize(const JsonObject & object) = 0;
  };
};

#endif
