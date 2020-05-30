#ifndef Redux_Store_hpp
#define Redux_Store_hpp

#include "Reducer.hpp"
#include "Subscriber.hpp"
#include "Action.hpp"

namespace Redux {
  class Store {

    public:

      void setup(Reducer * reducer, Subscriber * subscriber) {
        _reducer = reducer;
        _subscriber = subscriber;
        _state = _reducer->init();
        _subscriber->notify();
      }

      void dispatch(const Action & action) {
        _state = _reducer->reduce(_state, action);
        _subscriber->notify();
      }

      template <class T>
      const T * getState() {
        return _state->as<T>();
      }

    private:
      const State * _state = NULL;
      const Reducer * _reducer;
      const Subscriber * _subscriber;

  };
}

#endif
