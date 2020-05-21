#ifndef JsonFile_hpp
#define JsonFile_hpp

#include <ArduinoJson.h>

#include "Debug.hpp"

class JsonFile {
  const char *_path;

  public:
    JsonFile(const char *path);
    void read(JsonDocument *pDoc);
    void write(JsonDocument *pDoc);
    void remove();
};

JsonFile::JsonFile(const char *path) {
  _path = path;
}

void JsonFile::read(JsonDocument *pDoc) {
  DEBUG_VAL(F("check file"), F("path"), _path);
  if (Storage::exists(_path)) {
    File file = Storage::open(_path, "r");
    if (file) {
      DEBUG_LIST_START(F("Opened file"));
      DEBUG_LIST_VAL(F("path"), _path);
      DEBUG_LIST_VAL(F("size"), file.size());
      // This call to readString moves the file stream to the end
      // when DEBUG is enabled
      DEBUG_LIST_VAL(F("contents"), file.readString());
      DEBUG_LIST_END;
      // This call to seek moves the file stream back to the beginning
      // when DEBUG is enabled so that the deserialize can work
      DEBUG_DO(file.seek(0, SeekSet));
      DeserializationError error = deserializeJson(*pDoc, file);
      if (error) {
        DEBUG_LIST_START(F("Failed to deserialize file"));
        DEBUG_LIST_VAL(F("path"), _path);
        DEBUG_LIST_VAL(F("error"), error.c_str());
        DEBUG_LIST_END;
      }
      file.close();
      return;
    }
    DEBUG_VAL(F("Failed to open file"), F("path"), _path);
    return;
  }
  DEBUG_VAL(F("File does not exist"), F("path"), _path);
}

void JsonFile::write(JsonDocument *pDoc) {
  File file = Storage::open(_path, "w");
  if (file) {
    DEBUG_VAL(F("Opened file"), F("path"), _path);
    if (serializeJson(*pDoc, file) == 0) {
      DEBUG_VAL(F("Failed to write file"), F("path"), _path);
    }
    DEBUG_LIST_START(F("Wrote file"));
    DEBUG_LIST_VAL(F("path"), _path);
    DEBUG_LIST_VAL(F("size"), file.size());
    DEBUG_LIST_END;
    file.close();
    return;
  }
  DEBUG_VAL(F("Failed to open file"), F("path"), _path);
}

void JsonFile::remove() {
  if (!Storage::remove(_path)) {
    DEBUG_VAL(F("Failed to remove file"), F("path"), _path);
  }
  DEBUG_VAL(F("Removed file"), F("path"), _path);
}

#endif
