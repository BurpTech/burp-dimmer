#include "./util.hpp"

using f_onObj = std::function<void(JsonObject & obj)>;
void withObj(f_onObj onObj) {
  StaticJsonDocument<1024> doc;
  JsonObject obj = doc.to<JsonObject>();
  onObj(obj);
}
