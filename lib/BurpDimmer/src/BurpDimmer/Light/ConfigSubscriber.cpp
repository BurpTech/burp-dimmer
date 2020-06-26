#include "ActionType.hpp"
#include "Actions.hpp"
#include "ConfigSubscriber.hpp"

namespace BurpDimmer {
  namespace Light {

    ConfigSubscriber::ConfigSubscriber(Store::Interface & store) :
      _store(store)
    {}

    void ConfigSubscriber::setup(const Config * config) {
      // do nothing
    }

    void ConfigSubscriber::onPublish(const Config * config) {
      applyConfig(_store.getState(), config, [&](const Error error, const State::Params * params) {
          if (Error::noError == error) {
            _store.dispatch(Action(*params));
          }
      });
    }

  }
}
