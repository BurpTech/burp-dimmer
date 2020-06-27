#include "ActionType.hpp"
#include "Actions.hpp"
#include "ConfigSubscriber.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    ConfigSubscriber::ConfigSubscriber(Store::Interface & store) :
      _store(store)
    {}

    void ConfigSubscriber::setup(const Config * config) {
      // do nothing
    }

    void ConfigSubscriber::onPublish(const Config * config) {
      State::Params params;
      applyConfig(_store.getState(), config, params);
      if (State::Error::noError == params.error) {
        _store.dispatch(Action(params));
      }
    }

  }
}
