#include "Actions.hpp"
#include "Deserialize.hpp"

namespace BurpDimmer {
  namespace Light {

    void deserialize(const JsonObject & object, f_onState onState) {
      deserialize(object, [&](const Error error, const Params * params) {
          onState(memory.create(params));
      });
    }

  }
}
