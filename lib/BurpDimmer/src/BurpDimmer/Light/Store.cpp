#include "Reducer.hpp"
#include "ConfigSubscriber.hpp"
#include "Store.hpp"

namespace BurpDimmer {
  namespace Light {

    Store * store;

    void init(const State::Instance * state) {
      store = new Store(reducer, state);
      initConfigSubscriber(*store);
    }

    void deinit() {
      deinitConfigSubscriber();
      delete store;
    }

  }
}
