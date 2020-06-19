#pragma once

#include <CppRedux/Subscriber.hpp>
#include <CppRedux/Selector.hpp>
#include <BurpDimmer/Config.hpp>

namespace BurpDimmer {
  namespace Network {

    class Manager : CppRedux::Subscriber {

      public:

        Manager();
        void notify() override;

      private:

        using State = Config::Network::Manager::State;
        CppRedux::Selector<Config::State, State> _selector;
        static const State * _select(const Config::State * state);

    };

  }
}
