#include "Config/Deserialize.hpp"
#include "Config/Reducer.hpp"
#include "Config.hpp"

namespace BurpDimmer {
  namespace Config {

    Store store;

    void init(const JsonObject & object) {
      deserialize(object, [](const State * initialState) {
          store.setReducer(&reducer, initialState);
      });
    }

  }
}
