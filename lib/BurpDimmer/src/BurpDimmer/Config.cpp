#include "Config/Deserialize.hpp"
#include "Config/Store.hpp"
#include "Config.hpp"

namespace BurpDimmer {
  namespace Config {

    void read(const JsonObject & object) {
      deserialize(object, setup);
    }

  }
}
