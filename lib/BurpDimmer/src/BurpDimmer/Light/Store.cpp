#include "Reducer.hpp"
#include "ConfigSubscriber.hpp"
#include "Store.hpp"

namespace BurpDimmer {
  namespace Light {

    Store store(reducer);

    void setup(const State::Instance * state) {
      store.setup(state);
    }

    void reportSubscriberCounts() {
      REPORT_SUBSCRIBER_COUNT("Light::store", store);
    }

  }
}
