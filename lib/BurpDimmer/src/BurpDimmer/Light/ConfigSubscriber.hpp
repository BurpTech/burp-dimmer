#pragma once

#include <BurpTree/Subscriber.hpp>
#include "../Logger.hpp"
#include "Config.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    template <class Updater>
    class ConfigSubscriber : public BurpTree::Subscriber<Config> {

      public:

        ConfigSubscriber(Updater & updater) :
          _updater(updater),
          _logger("Light::ConfigSubscriber")
        {}

        void setup(const Config * initial) override {
          _updater.getFactory().setConfig(initial);
        }

        void update(const Config * next) override {
          using namespace std::placeholders;
          _logger.status(_updater.update(std::bind(&Factory::applyConfig, _1, next)));
        }

      private:

        Updater & _updater;
        Logger _logger;

    };

  }
}
