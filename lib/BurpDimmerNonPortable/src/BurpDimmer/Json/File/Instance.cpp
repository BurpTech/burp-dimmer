#include <LittleFS.h>
#include "Instance.hpp"

namespace BurpDimmer {
  namespace Json {
    namespace File {

      Instance::Instance(const BurpLogger::Logger * logger, const char * path) :
        _logger(logger),
        _path(path)
      {}

      void Instance::read(JsonDocument & doc) const {
        _logger->info("check file: path: [%s]", _path);
        if (LittleFS.exists(_path)) {
          fs::File file = LittleFS.open(_path, "r");
          if (file) {
            DeserializationError error = deserializeJson(doc, file);
            if (error) {
              _logger->info("Failed to deserialize file: path: [%s]: error [%s]", _path, error.c_str());
            }
            file.close();
            return;
          }
          _logger->info("Failed to open file: path: [%s]", _path);
          return;
        }
        _logger->info("File does not exist: path: [%s]", _path);
      }

      void Instance::write(JsonDocument & doc) const {
        fs::File file = LittleFS.open(_path, "w");
        if (file) {
          _logger->info("Opened file: path: [%s]", _path);
          if (serializeJson(doc, file) == 0) {
            _logger->info("Failed to write file: path: [%s]", _path);
          }
          _logger->info("Wrote file: path: [%s]: size: [%d]", _path, file.size());
          file.close();
          return;
        }
        _logger->info("Failed to open file: path: [%s]", _path);
      }

      void Instance::remove() {
        if (!LittleFS.remove(_path)) {
          _logger->info("Failed to remove file: path: [%s]", _path);
        }
        _logger->info("Removed file: path: [%s]", _path);
      }

    }
  }
}
