#pragma once

#include <functional>
#include <BurpTree/Subscriber.hpp>

namespace BurpDimmer {
  namespace ConfigFile {

    using f_withObj = std::function<void(const JsonObject & object)>;

    template <class Config>
    class Interface : public BurpTree::Subscriber<Config> {

      public:

        virtual void read(f_withObj withObj) = 0;

    };

  }
}
