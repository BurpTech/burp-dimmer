#include "Selector.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Light {

      const State::Instance * select(const Config::State::Instance * state) {
        return state->light;
      }

      Selector selector(select);

      void setup(const Config::State::Instance * state) {
        selector.setup(state);
      }

      void reportSubscriberCounts() {
        REPORT_SUBSCRIBER_COUNT("Config::Light::selector", selector);
      }

    }
  }
}
