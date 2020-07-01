#pragma once

#include <BurpTree/Subscriber.hpp>
#include <BurpDimmer/Config/Network/Manager/State.hpp>

namespace BurpDimmer {
  namespace Network {
    namespace Manager {

      using Config = Config::Network::Manager::State;

      class Instance : public BurpTree::Subscriber {

        public:

          Instance();
          void setup(const BurpTree::State * state) override;
          void onPublish(const BurpTree::State * state) override;

        private:

          const Config * _config;

      };

    }
  }
}
