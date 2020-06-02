#include <Redux/Subscriber.hpp>
#include "./helpers/util.hpp"
#include "./Config.hpp"
#include "./Config/Network.hpp"
#include "ActionType.hpp"
#include "ArduinoJson.hpp"
#include "Redux/Reducer.hpp"

namespace Config {

  class Subscriber : public Redux::Subscriber {
    public:
      const State * state = nullptr;
      void notify() override {
        state = store.getState();
      }
  };
  Subscriber subscriber;

  const State * state() {
    return subscriber.state;
  }

  void initialize() {
    // initialize the subscriber
    subscriber.state = nullptr;
    // initialize the state
    store.setup(&reducer, &subscriber);
    withObj([&](JsonObject & object) {
      object["network"]["manager"][Network::Manager::State::MODE_FIELD] = static_cast<int>(Network::Manager::PermMode::ACCESS_POINT);
      object["network"]["manager"][Network::Manager::State::ACCESS_POINT_TIMEOUT_FIELD] = 60000;
      store.init([&](Redux::Reducer<State, ActionType, JsonObject>::f_doInit doInit) {
        return doInit(&object);
      });
    });
  }

  void test() {
    Network::test();
  }

}
