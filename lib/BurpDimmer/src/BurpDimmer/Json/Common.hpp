#pragma once

#include <ArduinoJson.h>

#include "../Debug.hpp"

namespace BurpDimmer {
  namespace Json {

    using f_onObj = std::function<void(JsonObject & obj)>;
    using f_onDoc = std::function<void(JsonDocument & doc)>;
    using f_withDoc = std::function<void(f_onDoc callback)>;

  }
}
