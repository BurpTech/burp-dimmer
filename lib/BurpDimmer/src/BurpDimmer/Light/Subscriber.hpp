#pragma once

#include <CppRedux/Subscriber.hpp>
#include <CppRedux/Selector.hpp>
#include "../Config/State.hpp"

namespace BurpDimmer {
  namespace Light {

    class Subscriber : public CppRedux::Subscriber {

      public:

        Subscriber();
        void notify() override;

      private:

        using State = Config::Light::State;
        using Selector = CppRedux::Selector<Config::State, State>;
        Selector _selector;
        static const State * _select(const Config::State * state);

    };

    extern Subscriber subscriber;

  }
}
