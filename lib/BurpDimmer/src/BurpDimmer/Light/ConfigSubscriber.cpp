#include "ActionType.hpp"
#include "Actions.hpp"
#include "ConfigSubscriber.hpp"

namespace BurpDimmer {
  namespace Light {

    ConfigSubscriber::ConfigSubscriber(Store & store) :
      _store(store)
    {}

    void ConfigSubscriber::notify() {
      applyConfig(_store.getState(), [&](const Error error, const Params * params) {
          if (Error::noError == error) {
            _store.dispatch(Action(ActionType::SET_STATE, params));
          }
      });
    }

  }
}
