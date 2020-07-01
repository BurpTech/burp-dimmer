#pragma once

#include <BurpTree/Dispatcher.hpp>
#include <BurpTree/Subscriber.hpp>
#include "../Logger.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    class ConfigSubscriber : public BurpTree::Subscriber {

      public:

        ConfigSubscriber(BurpTree::Dispatcher<Factory> & dispatcher, Factory & factory);
        void setup(const BurpTree::State * initial) override;
        void onPublish(const BurpTree::State * next) override;

      private:

        BurpTree::Dispatcher<Factory> & _dispatcher;
        Factory & _factory;
        Logger _logger;

    };

  }
}
