#pragma once

#include "./Subscriber.hpp"

namespace Redux {

  class SubscriberList : public Subscriber {

    public:

      SubscriberList(Subscriber ** subscribers) :
        _subscribers(subscribers) {
      }

      void notify() override {
        Subscriber ** subscriber = _subscribers;
        while (*subscriber) {
          (*subscriber)->notify();
          subscriber++;
        }
      }

    private:

      Subscriber ** _subscribers;

  };

}
