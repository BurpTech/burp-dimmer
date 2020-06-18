#pragma once

#include <LittleFS.h>

namespace BurpDimmer {

  class Storage {
    public:
      static void begin() {
        LittleFS.begin();
      }

      static File open(String path, const char *mode) {
        return LittleFS.open(path, mode);
      }

      static bool exists(String path) {
        return LittleFS.exists(path);
      }

      static bool remove(String path) {
        return LittleFS.remove(path);
      }
  };

}
