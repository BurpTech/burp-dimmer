#pragma once

#include <functional>
#include <BurpRedux/Subscriber/Interface.hpp>
#include "../Light/State.hpp"

namespace BurpDimmer {
  namespace LightFile {

    class Interface : public BurpRedux::Subscriber::Interface<Light::State::Instance> {

      public:

        using f_withObj = std::function<void(const JsonObject & object)>;

        virtual void read(f_withObj withObj) = 0;
        virtual void loop() = 0;

    };

  }
}
