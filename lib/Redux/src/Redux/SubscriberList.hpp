#pragma once

#include "./Subscriber.hpp"

namespace Redux {

  class SubscriberList : public Subscriber {

    public:

      SubscriberList(Subscriber ** subscribers);
      void notify() override;

    private:

      Subscriber ** _subscribers;

  };

}
