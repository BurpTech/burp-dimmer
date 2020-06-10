#pragma once

#include <ArduinoJson.h>
#include <functional>

using f_onObj = std::function<void(JsonObject & obj)>;
void withObj(f_onObj onObj);
