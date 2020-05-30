#ifndef Redux_SubscriberList_hpp
#define Redux_SubscriberList_hpp

#include "./Subscriber.hpp"

namespace Redux {

  class SubscriberList : public Subscriber {

    public:

      SubscriberList(const Subscriber ** subscribers) :
        _subscribers(subscribers) {
      }

      void notify() const {
        const Subscriber ** subscriber = _subscribers;
        while (*subscriber) {
          (*subscriber)->notify();
          subscriber++;
        }
      }

    private:

      const Subscriber ** _subscribers;

  };

}

#endif
