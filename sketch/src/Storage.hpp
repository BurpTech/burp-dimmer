#ifndef Storage_hpp
#define Storage_hpp

#include "Debug.hpp"

#include <LittleFS.h>

class Storage {
  public:
    static void begin();
    static File open(String path, const char *mode);
    static bool exists(String path);
    static bool remove(String path);
};

void Storage::begin() {
  LittleFS.begin();
}

File Storage::open(String path, const char *mode) {
  return LittleFS.open(path, mode);
}

bool Storage::exists(String path) {
  return LittleFS.exists(path);
}

bool Storage::remove(String path) {
  return LittleFS.remove(path);
}

#endif
