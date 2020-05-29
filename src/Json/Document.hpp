#ifndef Json_Document_hpp
#define Json_Document_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Json.hpp"

namespace Json {
  class Document {
    public:
      virtual void serialize(JsonDocument & doc) = 0;
      virtual void deserialize(JsonDocument & doc) = 0;
  };
};

#endif
