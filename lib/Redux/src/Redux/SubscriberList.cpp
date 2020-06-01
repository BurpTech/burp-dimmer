#include "./SubscriberList.hpp"

namespace Redux {

  SubscriberList::SubscriberList(Subscriber ** subscribers) :
    _subscribers(subscribers) {
  }

  void SubscriberList::notify() {
    Subscriber ** subscriber = _subscribers;
    while (*subscriber) {
      (*subscriber)->notify();
      subscriber++;
    }
  }

}
