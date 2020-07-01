#pragma once

#include <BurpTree/Status.hpp>

namespace BurpDimmer {
  
  class Logger {

    public:

      using Status = BurpTree::Status;
      Logger(const char * label);
      void status(const Status & status);

    private:
      
      static const char * _format;
      const char * _label;

  };

}
