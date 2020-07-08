#pragma once

#include <ArduinoJson.h>

namespace BurpDimmer {
  namespace Json {
    using f_onDoc = std::function<void(JsonDocument & doc)>;

    template <size_t size>
    void withStaticDoc(f_onDoc onDoc) {
      StaticJsonDocument<size> doc;
      onDoc(doc);
    }

  }
}
