#include "../Config.hpp"
#include "../Light.hpp"
#include "ActionType.hpp"
#include "Actions.hpp"
#include "Subscriber.hpp"

namespace BurpDimmer {
  namespace Light {

    Subscriber subscriber;

    const Subscriber::State * Subscriber::_select(const Config::State * state) {
      return state->light;
    }

    Subscriber::Subscriber() :
      _selector(_select)
    {}

    void Subscriber::notify() {
      _selector.check(Config::store.getState(), [](const State * state) {
          applyConfig(store.getState(), [](const Error error, const Params * params) {
              if (Error::noError == error) {
                store.dispatch(Action(ActionType::SET_STATE, params));
              }
          });
      });
    }

  }
}
