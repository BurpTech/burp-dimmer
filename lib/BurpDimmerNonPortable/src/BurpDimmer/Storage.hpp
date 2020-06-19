#pragma once

#include <LittleFS.h>

namespace BurpDimmer {

  class Storage {
    public:
      static void begin() {
        LittleFS.begin();
      }

      static File open(const char * path, const char *mode) {
        return LittleFS.open(path, mode);
      }

      static bool exists(const char * path) {
        return LittleFS.exists(path);
      }

      static bool remove(const char * path) {
        return LittleFS.remove(path);
      }
  };

}
