#pragma once

#include <CppRedux/Subscriber.hpp>
#include <BurpDimmer/Light.hpp>

namespace BurpDimmer {
  namespace Components {

    class Light : public CppRedux::Subscriber {

      public:

        using Store = BurpDimmer::Light::Store;

        Light(int pin, const Store & store);
        void setup();
        void notify() override;

      private:

        int _pin;
        const Store & _store;

    };

  }
}
