#ifndef JsonDocument_hpp
#define JsonDocument_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Json.hpp"

namespace Json {
  class Document {
    public:
      virtual void serialize(JsonDocument * pDoc) = 0;
      virtual void deserialize(JsonDocument * pDoc) = 0;
  };
};

#endif
