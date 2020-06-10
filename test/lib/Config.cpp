#include <Redux/Subscriber.hpp>
#include "./helpers/util.hpp"
#include "./Config.hpp"
#include "./Config/Network.hpp"
#include "ActionType.hpp"
#include "ArduinoJson.hpp"
#include "Redux/Reducer.hpp"

namespace Config {

  class Subscriber : public Redux::Subscriber<State> {
    public:
      const State * state = nullptr;
      void notify(const State * s) override {
        state = s;
      }
  };
  Subscriber subscriber;

  const State * state() {
    return subscriber.state;
  }


  void _initialize(f_onObj onObj) {
    // initialize the subscriber
    subscriber.state = nullptr;
    // initialize the state
    store.setup(&reducer, &subscriber);
    withObj([&](JsonObject & object) {
      onObj(object);
      store.init(object);
    });
  }

  void initializeDefaults() {
    _initialize([&](JsonObject & object) {});
  }

  void initialize() {
    _initialize([&](JsonObject & object) {
      object["network"]["manager"][Network::Manager::State::MODE_FIELD] = static_cast<int>(Network::Manager::PermMode::ACCESS_POINT);
      object["network"]["manager"][Network::Manager::State::ACCESS_POINT_TIMEOUT_FIELD] = 60000;
    });
  }

  void test() {
    Network::test();
  }

}
