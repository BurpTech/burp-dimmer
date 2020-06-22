#pragma once

#include <BurpRedux/Subscriber.hpp>
#include <BurpDimmer/Config/Network/Manager/State.hpp>

namespace BurpDimmer {
  namespace Network {
    namespace Manager {

      using State = Config::Network::Manager::State::Instance;

      class Instance : public BurpRedux::Subscriber<State> {

        public:


          Instance();
          void setup(const State * state);
          void onPublish(const State * state) override;

        private:

          const State * _state;

      };

      extern Instance instance;
      void setup(const State * state);

    }
  }
}
