#include "Light/Deserialize.hpp"
#include "Light/Reducer.hpp"
#include "Light.hpp"

namespace BurpDimmer {
  namespace Light {

    Store store;

    void init(const JsonObject & object) {
      deserialize(object, [](const State * initialState) {
          store.setReducer(&reducer, initialState);
      });
    }

  }
}
