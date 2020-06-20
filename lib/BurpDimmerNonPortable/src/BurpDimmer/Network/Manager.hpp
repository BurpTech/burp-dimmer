#pragma once

#include <CppRedux/Subscriber.hpp>
#include <CppRedux/Selector.hpp>
#include <BurpDimmer/Config.hpp>

namespace BurpDimmer {
  namespace Network {

    class Manager : public CppRedux::Subscriber {

      public:

        using Selector = Config::Network::Manager::Selector;

        Manager(const Selector & selector);
        void notify() override;

      private:

        const Selector & _selector;

    };

    extern Manager manager;

  }
}
