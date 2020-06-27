#pragma once

#include <BurpRedux/Subscriber/Interface.hpp>
#include <BurpDimmer/Config/Network/Manager/State.hpp>

namespace BurpDimmer {
  namespace Network {
    namespace Manager {

      using State = Config::Network::Manager::State::Instance;

      class Instance : public BurpRedux::Subscriber::Interface<State> {

        public:

          Instance();
          void setup(const State * state) override;
          void onPublish(const State * state) override;

        private:

          const State * _state;

      };

    }
  }
}
