#include "ActionType.hpp"
#include "Actions.hpp"
#include "ConfigSubscriber.hpp"

namespace BurpDimmer {
  namespace Light {

    ConfigSubscriber::ConfigSubscriber(Store & store) :
      _store(store)
    {}

    void ConfigSubscriber::onPublish(const Config * config) {
      applyConfig(_store.getState(), config, [&](const Error error, const State::Params * params) {
          if (Error::noError == error) {
            _store.dispatch(Action(ActionType::SET_STATE, params));
          }
      });
    }

    ConfigSubscriber configSubscriber(store);

  }
}
