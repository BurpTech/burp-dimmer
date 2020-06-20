#pragma once

#include <CppRedux/Subscriber.hpp>

namespace BurpDimmer {
  namespace Components {

    class Light : public CppRedux::Subscriber {

      public:

        Light(int pin);
        void setup();
        void notify() override;

      private:

        int _pin;

    };

  }
}
