#pragma once

#include "Reducer.hpp"
#include "Subscriber.hpp"
#include "Action.hpp"

namespace Redux {

  template <class ActionType>
  class Store {

    public:

      Store() :
        _state(nullptr) {
      }

      void setup(const Reducer<ActionType> * reducer, Subscriber * subscriber) {
        _reducer = reducer;
        _subscriber = subscriber;
        _state = _reducer->init();
        _subscriber->notify();
      }

      void dispatch(const Action<ActionType> & action) {
        _state = _reducer->reduce(_state, action);
        _subscriber->notify();
      }

      template <class DerivedState>
      const DerivedState * getState() const {
        return _state->as<DerivedState>();
      }

    private:

      const State * _state;
      const Reducer<ActionType> * _reducer;
      Subscriber * _subscriber;

  };
}
