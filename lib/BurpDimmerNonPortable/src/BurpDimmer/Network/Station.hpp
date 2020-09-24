#pragma once

#include <BurpLogger.hpp>
#include <BurpTree/Subscriber.hpp>
#include <BurpDimmer/Config/Network/Station/State.hpp>

namespace BurpDimmer {
  namespace Network {
    namespace Station {

      using Config = Config::Network::Station::State;

      class Instance : public BurpTree::Subscriber<Config> {

        public:

          Instance(const BurpLogger::Logger * logger);
          void setup(const Config * initial) override;
          void update(const Config * next) override;

        private:

          const BurpLogger::Logger * _logger;
          const Config * _config;

      };

    }
  }
}
