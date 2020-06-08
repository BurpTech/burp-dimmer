#pragma once

#include <Util/Debug.hpp>
#include "Reducer.hpp"
#include "Subscriber.hpp"
#include "Action.hpp"

namespace Redux {

  template <class State, class ActionType, class InitParams>
  class Store {

    public:

      Store() :
        _state(nullptr),
        _lastState(nullptr) {
      }

      void setup(const Reducer<State, ActionType, InitParams> * reducer, Subscriber<State> * subscriber) {
        _reducer = reducer;
        _subscriber = subscriber;
      }

      void loop() {
        // Notify asynchronously so that 
        // actions can be batched synchronously.
        // State reduction is always synchronous
        if (_state != _lastState) {
          _notifying = true;
          _subscriber->notify(_state);
          _notifying = false;
        }
      }

      void init(const InitParams & initParams) {
        // Passing the state to _reducer->init 
        // allows us to reinitialize the reducer
        // without leaking memory as the state
        // will not be nullptr if init is called
        // twice
        _reducing = true;
        _state = _reducer->init(_state, initParams);
        _reducing = false;
      }

      void dispatch(const Action<ActionType> & action) {
        if (_reducing) {
          BURP_DEBUG_ERROR("Reducers cannot dispatch actions!!: Action.type: [%d]", action.type);
        } else {
          if (_notifying) {
            BURP_DEBUG_WARN("Are you sure you meant to dispatch an action during notification, it's possible that not all subscribers will have seen the previous state: Action.type: [%d]", action.type);
          }
          _reducing = true;
          _state = _reducer->reduce(_state, action);
          _reducing = false;
        }
      }

      State getState() {
        return _state;
      }

    private:

      const State * _state = nullptr;
      const State * _lastState = nullptr;
      const Reducer<State, ActionType, InitParams> * _reducer = nullptr;
      Subscriber<State> * _subscriber = nullptr;
      bool _reducing = false;
      bool _notifying = false;

  };
}
