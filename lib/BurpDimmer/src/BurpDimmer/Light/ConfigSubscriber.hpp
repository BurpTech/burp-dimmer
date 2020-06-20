#pragma once

#include <CppRedux/Subscriber.hpp>
#include <CppRedux/Selector.hpp>
#include "Store.hpp"

namespace BurpDimmer {
  namespace Light {

    class ConfigSubscriber : public CppRedux::Subscriber {

      public:

        ConfigSubscriber(Store & store);
        void notify() override;

      private:

        Store & _store;

    };

  }
}
