#pragma once

namespace Redux {
  class Subscriber {

    public:

      virtual void notify() = 0;

  };
}
