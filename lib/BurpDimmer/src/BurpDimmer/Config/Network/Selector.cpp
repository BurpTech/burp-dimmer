#include "Selector.hpp"
#include "AccessPoint/Selector.hpp"
#include "Manager/Selector.hpp"
#include "Station/Selector.hpp"

namespace BurpDimmer {
  namespace Config {
    namespace Network {

      Selector * selector;

      const State::Instance * select(const Config::State::Instance * state) {
        return state->network;
      }

      void init(const Config::State::Instance * state) {
        selector = new Selector(select, state);
        AccessPoint::init(selector->getState());
        selector->subscribe(AccessPoint::selector);
        Manager::init(selector->getState());
        selector->subscribe(Manager::selector);
        Station::init(selector->getState());
        selector->subscribe(Station::selector);
      }

      void deinit() {
        Station::deinit();
        Manager::deinit();
        AccessPoint::deinit();
        delete selector;
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
