#ifndef Json_hpp
#define Json_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

namespace Json {
  using f_onObj = std::function<void(JsonObject *pObj)>;
  using f_onDoc = std::function<void(JsonDocument *pDoc)>;
  using f_withDoc = std::function<void(f_onDoc callback)>;
};

#endif
