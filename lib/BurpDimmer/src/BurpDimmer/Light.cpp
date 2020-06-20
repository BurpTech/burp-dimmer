#include "Light/Deserialize.hpp"
#include "Light.hpp"

namespace BurpDimmer {
  namespace Light {

    Store store;
    ConfigSubscriber configSubscriber(store);

    void init(Store & store, const Reducer & reducer, const JsonObject & object) {
      deserialize(object, [&](const State * initialState) {
          store.setReducer(&reducer, initialState);
      });
    }

  }
}
