#include "Selector.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {
      namespace AccessPoint {

        Selector * selector;

        const State::Instance * select(const Network::State::Instance * state) {
          return state->accessPoint;
        }

        void init(const Network::State::Instance * state) {
          selector = new Selector(select, state);
        }

        void deinit() {
          delete selector;
        }

        void reportSubscriberCounts() {
          REPORT_SUBSCRIBER_COUNT("Config::Network::AccessPoint::selector", selector);
        }

      }
    }
  }
}
