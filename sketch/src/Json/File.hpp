#ifndef JsonFile_hpp
#define JsonFile_hpp

#include <ArduinoJson.h>

#include "../Debug.hpp"

#include "Document.hpp"

namespace Json {
  class File: public Json::Document {
    const char *_path;

    public:
      File(const char *path) :
        _path(path) {
      }

      void deserialize(JsonDocument *pDoc) {
        DEBUG_PRINT("check file: path: [%s]", _path);
        if (Storage::exists(_path)) {
          fs::File file = Storage::open(_path, "r");
          if (file) {
            DEBUG_DO({
              // wrapped so we rewind the file after reading it for debug
              DEBUG_PRINT("Opened file: path [%s]: size: [%d]: contents: [%s]", _path, file.size(), file.readString().c_str());
              file.seek(0, SeekSet);
            });
            DeserializationError error = deserializeJson(*pDoc, file);
            if (error) {
              DEBUG_PRINT("Failed to deserialize file: path: [%s]: error [%s]", _path, error.c_str());
            }
            file.close();
            return;
          }
          DEBUG_PRINT("Failed to open file: path: [%s]", _path);
          return;
        }
        DEBUG_PRINT("File does not exist: path: [%s]", _path);
      }

      void serialize(JsonDocument *pDoc) {
        fs::File file = Storage::open(_path, "w");
        if (file) {
          DEBUG_PRINT("Opened file: path: [%s]", _path);
          if (serializeJson(*pDoc, file) == 0) {
            DEBUG_PRINT("Failed to write file: path: [%s]", _path);
          }
          DEBUG_PRINT("Wrote file: path: [%s]: size: [%d]", _path, file.size());
          file.close();
          return;
        }
        DEBUG_PRINT("Failed to open file: path: [%s]", _path);
      }

      void remove() {
        if (!Storage::remove(_path)) {
          DEBUG_PRINT("Failed to remove file: path: [%s]", _path);
        }
        DEBUG_PRINT("Removed file: path: [%s]", _path);
      }
  };
};

#endif
