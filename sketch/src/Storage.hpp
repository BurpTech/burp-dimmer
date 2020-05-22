#ifndef Storage_hpp
#define Storage_hpp

#include "Debug.hpp"

#include <LittleFS.h>

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

#endif
