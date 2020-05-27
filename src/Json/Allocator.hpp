#ifndef JsonAllocator_hpp
#define JsonAllocator_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Json.hpp"

namespace Json {
  template <class T>
  class Allocator {
    public:
      static void withDoc(f_onDoc onDoc) {
        DEBUG_PRINT("creating temporary JSON document");
        T doc;
        onDoc(&doc);
      }
  };
};

#endif
