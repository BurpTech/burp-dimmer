#pragma once

#include "Common.hpp"

namespace BurpDimmer {
  namespace Json {

    class ConfigSection : public Object {
      public:
        using f_onChange = std::function<void()>;

        const char * name;

        ConfigSection(const char * name, f_onChange onChange) :
          name(name),
          _onChange(onChange) {
        }

      private:
        f_onChange _onChange;
    };

  }
}
