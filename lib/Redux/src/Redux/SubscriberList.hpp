#pragma once

#include "./Subscriber.hpp"

namespace Redux {

  template <class State>
  class SubscriberList : public Subscriber<State> {

    public:

      SubscriberList(Subscriber<State> ** subscribers)
        : _subscribers(subscribers)
      {}

      void notify(const State * state) override
      {
        Subscriber<State> ** subscriber = _subscribers;
        while (*subscriber)
        {
          (*subscriber)->notify(state);
          subscriber++;
        }
      }

    private:

      Subscriber<State> ** _subscribers;

  };

}
