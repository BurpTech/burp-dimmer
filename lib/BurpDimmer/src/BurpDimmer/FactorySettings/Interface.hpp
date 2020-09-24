#pragma once

namespace BurpDimmer {
  namespace FactorySettings {

    class Interface {

      public:

        virtual const char * getHostname() const = 0;
        virtual const char * getSsid() const = 0;
        virtual const char * getPassphrase() const = 0;

    };

  }
}
