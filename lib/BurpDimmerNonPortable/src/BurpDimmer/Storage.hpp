#pragma once

#include <LittleFS.h>

namespace BurpDimmer {

  class Storage {
    public:
      static void begin();
      static File open(const char * path, const char *mode);
      static bool exists(const char * path);
      static bool remove(const char * path);
  };

}
