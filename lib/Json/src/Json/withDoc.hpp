#pragma once

#include <ArduinoJson.h>
#include <Util/Debug.hpp>

namespace Json {
  using f_onDoc = std::function<void(JsonDocument & doc)>;

  template <class JsonDocumentClass>
  void withDoc(f_onDoc onDoc) {
    BURP_DEBUG_INFO("creating JSON document");
    JsonDocumentClass doc;
    onDoc(doc);
  }

}
