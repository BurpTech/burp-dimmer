#pragma once

#include <BurpTree/Root.hpp>
#include <BurpTree/Subscriber.hpp>

namespace BurpDimmer {
  namespace Light {

    class ConfigSubscriber : public BurpTree::Subscriber {

      public:

        ConfigSubscriber(BurpTree::Root & root);
        void setup(const BurpTree::State * initial) override;
        void onPublish(const BurpTree::State * next) override;

      private:

        BurpTree::Store & _store;

    };

  }
}
