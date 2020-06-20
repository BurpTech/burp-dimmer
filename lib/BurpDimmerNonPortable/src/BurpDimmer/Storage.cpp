#include "Storage.hpp"

namespace BurpDimmer {

  void Storage::begin() {
    LittleFS.begin();
  }

  File Storage::open(const char * path, const char *mode) {
    return LittleFS.open(path, mode);
  }

  bool Storage::exists(const char * path) {
    return LittleFS.exists(path);
  }

  bool Storage::remove(const char * path) {
    return LittleFS.remove(path);
  }

}
