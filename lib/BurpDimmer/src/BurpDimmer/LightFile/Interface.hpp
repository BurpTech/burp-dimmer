#pragma once

#include <functional>
#include <BurpTree/Subscriber.hpp>
#include "../Light/State.hpp"

namespace BurpDimmer {
  namespace LightFile {

    class Interface : public BurpTree::Subscriber<Light::State> {

      public:

        using f_withObj = std::function<void(const JsonObject & object)>;
        virtual void read(f_withObj withObj) = 0;
        virtual void loop() = 0;

    };

  }
}
