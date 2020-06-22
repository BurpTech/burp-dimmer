#pragma once

#include <ArduinoJson.h>
#include <BurpDebug.hpp>

namespace BurpDimmer {
  namespace Json {
    using f_onDoc = std::function<void(JsonDocument & doc)>;

    template <class JsonDocumentClass>
    void withDoc(f_onDoc onDoc) {
      JsonDocumentClass doc;
      BURP_DEBUG_INFO("created JSON document with size: %u", doc.capacity());
      onDoc(doc);
    }

  }
}
