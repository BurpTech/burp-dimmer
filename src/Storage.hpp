#ifndef Storage_hpp
#define Storage_hpp

#include "Debug.hpp"

#include <FS.h>

class Storage {
  public:
    static void begin() {
      SPIFFS.begin();
    }

    static File open(String path, const char *mode) {
      return SPIFFS.open(path, mode);
    }

    static bool exists(String path) {
      return SPIFFS.exists(path);
    }

    static bool remove(String path) {
      return SPIFFS.remove(path);
    }
};

#endif
