#pragma once

#include <BurpLogger.hpp>
#include <BurpTree/Subscriber.hpp>
#include "Config.hpp"
#include "State.hpp"

namespace BurpDimmer {
  namespace Light {

    template <class Updater>
    class ConfigSubscriber : public BurpTree::Subscriber<Config> {

      public:

        ConfigSubscriber(const BurpLogger::Logger * logger, Updater & updater) :
          _logger(logger),
          _updater(updater)
        {}

        void setup(const Config * initial) override {
          _updater.getFactory().setConfig(initial);
        }

        void update(const Config * next) override {
          using namespace std::placeholders;
          _logger.log("update config", _updater.update(std::bind(&Factory::applyConfig, _1, next)));
        }

      private:

        const BurpLogger::Logger * _logger;
        Updater & _updater;

    };

  }
}
