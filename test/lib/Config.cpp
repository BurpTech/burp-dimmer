#include <Redux/Subscriber.hpp>
#include "./Config.hpp"
#include "./Config/Network.hpp"

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

  void deserialize() {
    Network::deserialize();
  }

  void initialize() {
    // initialize the reducers
    deserialize();
    // initialize the subscriber
    subscriber.state = nullptr;
    // initialize the state
    store.setup(&reducer, &subscriber);
  }

  void test() {
    Network::test();
  }

}
