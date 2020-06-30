#include "ConfigSubscriber.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    ConfigSubscriber::ConfigSubscriber(BurpTree::Store & store) :
      _store(store)
    {}

    void ConfigSubscriber::setup(const BurpTree::State * initial) {
      // do nothing
    }

    void ConfigSubscriber::onPublish(const BurpTree::State * next) {
      State::Params params;
      applyConfig(_store.getState(), next, params);
      if (State::Error::noError == params.error) {
        _store.dispatch(Action(params));
      }
    }

  }
}
