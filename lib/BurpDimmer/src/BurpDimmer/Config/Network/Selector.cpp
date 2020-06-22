#include "Selector.hpp"
#include "AccessPoint/Selector.hpp"
#include "Manager/Selector.hpp"
#include "Station/Selector.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      const State::Instance * select(const Config::State::Instance * state) {
        return state->network;
      }

      Selector selector(select);

      void setup(const Config::State::Instance * state) {
        selector.setup(state);
        AccessPoint::setup(selector.getState());
        selector.subscribe(&AccessPoint::selector);
        Manager::setup(selector.getState());
        selector.subscribe(&Manager::selector);
        Station::setup(selector.getState());
        selector.subscribe(&Station::selector);
      }

      void reportSubscriberCounts() {
        REPORT_SUBSCRIBER_COUNT("Config::Network::selector", selector);
        AccessPoint::reportSubscriberCounts();
        Manager::reportSubscriberCounts();
        Station::reportSubscriberCounts();
      }

    }
  }
}
