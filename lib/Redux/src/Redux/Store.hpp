#pragma once

#include <Util/Debug.hpp>
#include "Reducer.hpp"
#include "Subscriber.hpp"
#include "Action.hpp"

namespace Redux {

  template <class State, class ActionType, class InitParams>
  class Store {

    public:

      Store(const Reducer<State, ActionType, InitParams> & reducer) :
        _state(nullptr),
        _lastState(nullptr),
        _reducer(reducer),
        _subscriber(nullptr),
        _reducing(false),
        _notifying(false)
      {}

      void setSubscriber(Subscriber * subscriber) {
        _subscriber = subscriber;
      }

      void loop() {
        // Notify asynchronously so that 
        // actions can be batched synchronously.
        // State reduction is always synchronous
        if (_state != _lastState) {
          _notifying = true;
          if (_subscriber) {
            _subscriber->notify();
          }
          _lastState = _state;
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
        _state = _reducer.init(_state, initParams);
        // prevent notification from init as subscribers
        // should be added afterwards anyway and they should
        // also be init'd if required to read the state
        _lastState = _state;
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
          _state = _reducer.reduce(_state, action);
          _reducing = false;
        }
      }

      const State * getState() {
        return _state;
      }

    private:

      const State * _state;
      const State * _lastState;
      const Reducer<State, ActionType, InitParams> & _reducer;
      Subscriber * _subscriber;
      bool _reducing;
      bool _notifying;

  };
}
