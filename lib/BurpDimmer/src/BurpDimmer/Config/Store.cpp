#include "Reducer.hpp"
#include "Light/Selector.hpp"
#include "Network/Selector.hpp"
#include "Store.hpp"

namespace BurpDimmer {
  namespace Config {

    Store store(reducer);

    void setup(const State::Instance * state) {
      store.setup(state);
      Light::setup(store.getState());
      store.subscribe(&Light::selector);
      Network::setup(store.getState());
      store.subscribe(&Network::selector);
    }

    void reportSubscriberCounts() {
      REPORT_SUBSCRIBER_COUNT("Config::store", store);
      Light::reportSubscriberCounts();
      Network::reportSubscriberCounts();
    }

  }
}
