#pragma once

#include <BurpTree/Subscriber.hpp>
#include <BurpDimmer/Config/Network/Manager/State.hpp>

namespace BurpDimmer {
  namespace Network {
    namespace Manager {

      using Config = Config::Network::Manager::State;

      class Instance : public BurpTree::Subscriber<Config> {

        public:

          Instance();
          void setup(const Config * initial) override;
          void update(const Config * next) override;

        private:

          const Config * _config;

      };

    }
  }
}
