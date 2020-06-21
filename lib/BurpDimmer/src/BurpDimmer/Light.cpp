#include "Light/Deserialize.hpp"
#include "Light/Store.hpp"
#include "Light.hpp"

namespace BurpDimmer {
  namespace Light {

    void read(const Config * config, const JsonObject & object) {
      deserialize(object, config, init);
    }

  }
}
