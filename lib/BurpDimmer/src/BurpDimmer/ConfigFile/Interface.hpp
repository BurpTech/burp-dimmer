#pragma once

#include <functional>
#include <BurpRedux/Subscriber/Interface.hpp>
#include "../Config/State.hpp"

namespace BurpDimmer {
  namespace ConfigFile {

    class Interface : public BurpRedux::Subscriber::Interface<Config::State::Instance> {

      public:

        using f_withObj = std::function<void(const JsonObject & object)>;

        virtual void read(f_withObj withObj) = 0;

    };

  }
}
