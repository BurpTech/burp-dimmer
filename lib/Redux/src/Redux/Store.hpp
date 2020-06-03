#pragma once

#include <Util/Debug.hpp>
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

      void init(const InitParams & initParams) {
        // Passing the state to _reducer->init 
        // allows us to reinitialize the reducer
        // without leaking memory as the state
        // will not be nullptr if init is called
        // twice
        state = _reducer->init(state, initParams);
        _subscriber->notify();
      }

      void dispatch(const Action<ActionType> & action) {
        if (_notifying) {
          BURP_DEBUG_ERROR("Cannot dispatch an action while notifying a changed state, you should probably wait for the next loop: Action.type: [%d]", action.type);
        } else {
          state = _reducer->reduce(state, action);
          _subscriber->notify();
        }
      }

    private:

      const Reducer<State, ActionType, InitParams> * _reducer;
      Subscriber * _subscriber;
      bool _notifying = false;

      void _notify() {
        _notifying = true;
        _subscriber->notify();
        _notifying = false;
      }

  };
}
