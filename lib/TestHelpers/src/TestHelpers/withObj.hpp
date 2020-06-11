#pragma once

#include <ArduinoJson.h>
#include <functional>

namespace TestHelpers {
  using f_onObj = std::function<void(JsonObject & obj)>;
  void withObj(f_onObj onObj);
}
