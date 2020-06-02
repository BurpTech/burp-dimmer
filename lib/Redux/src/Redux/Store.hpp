#pragma once

#include "Reducer.hpp"
#include "Subscriber.hpp"
#include "Action.hpp"

namespace Redux {

  template <class State, class ActionType, class InitParams>
  class Store {

    public:

      const State * state;

      Store() :
        state(nullptr) {
      }

      void setup(const Reducer<State, ActionType, InitParams> * reducer, Subscriber * subscriber) {
        _reducer = reducer;
        _subscriber = subscriber;
      }

      void init(const typename Reducer<State, ActionType, InitParams>::f_withInit withInit) {
        // Passing the state to _reducer->init 
        // allows us to reinitialize the reducer
        // without leaking memory as the state
        // will not be NULL if setup is called
        // twice
        state = _reducer->init(state, withInit);
        _subscriber->notify();
      }

      void dispatch(const Action<ActionType> & action) {
        state = _reducer->reduce(state, action);
        _subscriber->notify();
      }

    private:

      const Reducer<State, ActionType, InitParams> * _reducer;
      Subscriber * _subscriber;

  };
}
