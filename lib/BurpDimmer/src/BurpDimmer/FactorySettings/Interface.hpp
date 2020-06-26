#pragma once

namespace BurpDimmer {
  namespace FactorySettings {

    class Interface {

      public:

        virtual const char * getSsid() const = 0;
        virtual const char * getPassword() const = 0;

    };

  }
}
