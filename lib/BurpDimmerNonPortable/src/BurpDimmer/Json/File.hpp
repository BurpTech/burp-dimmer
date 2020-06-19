#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <BurpDimmer/Util/Debug.hpp>
#include "../Storage.hpp"

namespace BurpDimmer {
  namespace Json {

    class File {

      public:

        File(const char * path) :
          _path(path) {
        }

        void read(JsonDocument & doc) const {
          BURP_DEBUG_INFO("check file: path: [%s]", _path);
          if (Storage::exists(_path)) {
            fs::File file = Storage::open(_path, "r");
            if (file) {
              DeserializationError error = deserializeJson(doc, file);
              if (error) {
                BURP_DEBUG_INFO("Failed to deserialize file: path: [%s]: error [%s]", _path, error.c_str());
              }
              file.close();
              return;
            }
            BURP_DEBUG_INFO("Failed to open file: path: [%s]", _path);
            return;
          }
          BURP_DEBUG_INFO("File does not exist: path: [%s]", _path);
        }

        void write(JsonDocument & doc) const {
          fs::File file = Storage::open(_path, "w");
          if (file) {
            BURP_DEBUG_INFO("Opened file: path: [%s]", _path);
            if (serializeJson(doc, file) == 0) {
              BURP_DEBUG_INFO("Failed to write file: path: [%s]", _path);
            }
            BURP_DEBUG_INFO("Wrote file: path: [%s]: size: [%d]", _path, file.size());
            file.close();
            return;
          }
          BURP_DEBUG_INFO("Failed to open file: path: [%s]", _path);
        }

        void remove() {
          if (!Storage::remove(_path)) {
            BURP_DEBUG_INFO("Failed to remove file: path: [%s]", _path);
          }
          BURP_DEBUG_INFO("Removed file: path: [%s]", _path);
        }

      private:

        const char * _path;

    };

  }
}
