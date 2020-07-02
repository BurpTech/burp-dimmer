#pragma once

#include <BurpTree/Dispatcher.hpp>
#include <BurpTree/Subscriber.hpp>
#include "../Logger.hpp"
#include "Config.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    template <class Dispatcher>
    class ConfigSubscriber : public BurpTree::Subscriber<Config> {

      public:

        ConfigSubscriber(Dispatcher & dispatcher) :
          _dispatcher(dispatcher),
          _logger("Light::ConfigSubscriber")
        {}

        void setup(const Config * initial) override {
          _dispatcher.getFactory().setConfig(initial);
        }

        void update(const Config * next) override {
          using namespace std::placeholders;
          _logger.status(_dispatcher.dispatch(std::bind(&Factory::applyConfig, _1, next)));
        }

      private:

        Dispatcher & _dispatcher;
        Logger _logger;

    };

  }
}
