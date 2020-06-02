#pragma once

#include "Reducer.hpp"
#include "Subscriber.hpp"
#include "Action.hpp"

namespace Redux {

  template <class DerivedState, class ActionType>
  class Store {

    public:

      Store() :
        _state(nullptr) {
      }

      void setup(const Reducer<DerivedState, ActionType> * reducer, Subscriber * subscriber) {
        _reducer = reducer;
        _subscriber = subscriber;
        // Passing the _state to _reducer->init 
        // allows us to reinitialize the reducer
        // without leaking memory as the _state
        // will not be NULL if setup is called
        // twice
        _state = _reducer->init(_state);
        _subscriber->notify();
      }

      void dispatch(const Action<ActionType> & action) {
        _state = _reducer->reduce(_state, action);
        _subscriber->notify();
      }

      const DerivedState * getState() const {
        return _state->as<DerivedState>();
      }

    private:

      const State * _state;
      const Reducer<DerivedState, ActionType> * _reducer;
      Subscriber * _subscriber;

  };
}
