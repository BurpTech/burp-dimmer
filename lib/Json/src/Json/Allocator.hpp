#ifndef JsonAllocator_hpp
#define JsonAllocator_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Json.hpp"

namespace Json {
  using f_onDoc = std::function<void(JsonDocument & doc)>;
  using f_withDoc = std::function<void(f_onDoc onDoc)>;

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
