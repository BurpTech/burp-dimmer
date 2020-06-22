#include "Reducer.hpp"
#include "Light/Selector.hpp"
#include "Network/Selector.hpp"
#include "Store.hpp"

namespace BurpDimmer {
  namespace Config {

    Store * store;

    void init(const State::Instance * state) {
      store = new Store(reducer, state);
      Light::init(store->getState());
      store->subscribe(Light::selector);
      Network::init(store->getState());
      store->subscribe(Network::selector);
    }

    void deinit() {
      Network::deinit();
      Light::deinit();
      delete store;
    }

    void reportSubscriberCounts() {
      REPORT_SUBSCRIBER_COUNT("Config::store", store);
      Light::reportSubscriberCounts();
      Network::reportSubscriberCounts();
    }

  }
}
