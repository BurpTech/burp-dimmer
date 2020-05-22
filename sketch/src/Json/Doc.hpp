#ifndef JsonDoc_hpp
#define JsonDoc_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Json.hpp"

namespace Json {
  template <class T>
  class Doc {
    public:
      static void withDoc(f_onDoc onDoc) {
        DEBUG_MSG(F("creating temporary JSON document"));
        T doc;
        onDoc(&doc);
      }
  };
};

#endif
