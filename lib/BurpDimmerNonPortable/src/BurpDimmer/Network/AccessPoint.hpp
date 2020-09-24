#pragma once

#include <BurpLogger.hpp>
#include <BurpTree/Subscriber.hpp>
#include <BurpDimmer/Config/Network/AccessPoint/State.hpp>

namespace BurpDimmer {
  namespace Network {
    namespace AccessPoint {

      using Config = Config::Network::AccessPoint::State;

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
