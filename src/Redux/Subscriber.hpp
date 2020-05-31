#ifndef Redux_Subscriber_hpp
#define Redux_Subscriber_hpp

namespace Redux {
  class Subscriber {

    public:

      virtual void notify() = 0;

  };
}

#endif
