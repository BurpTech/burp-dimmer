#pragma once

#include <ArduinoJson.h>
#include <BurpDebug.hpp>

namespace BurpDimmer {
  namespace Json {
    using f_onDoc = std::function<void(JsonDocument & doc)>;

    template <size_t size>
    void withStaticDoc(f_onDoc onDoc) {
      StaticJsonDocument<size> doc;
      BURP_DEBUG_INFO("created JSON document with size: %u", doc.capacity());
      onDoc(doc);
    }

  }
}
