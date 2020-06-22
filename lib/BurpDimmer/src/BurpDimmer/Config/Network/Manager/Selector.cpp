#include "Selector.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace Manager {

        const State::Instance * select(const Network::State::Instance * state) {
          return state->manager;
        }

        Selector selector(select);

        void setup(const Network::State::Instance * state) {
          selector.setup(state);
        }

        void reportSubscriberCounts() {
          REPORT_SUBSCRIBER_COUNT("Config::Network::Manager::selector", selector);
        }

      }
    }
  }
}
