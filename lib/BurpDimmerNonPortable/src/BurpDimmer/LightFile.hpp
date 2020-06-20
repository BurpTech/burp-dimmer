#pragma once

#include <functional>
#include <CppRedux/Subscriber.hpp>
#include <BurpDimmer/Util/Debug.hpp>
#include <BurpDimmer/Json/withDoc.hpp>
#include <BurpDimmer/Config.hpp>
#include <BurpDimmer/Light.hpp>
#include "Json/File.hpp"

namespace BurpDimmer {

  template <class JsonDocumentClass>
  class LightFile : public CppRedux::Subscriber {

    public:

      LightFile(const char * path) :
        _file(path),
        _lastChange(0)
      {}

      void init() {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          _file.read(doc);
          Light::init(doc.as<JsonObject>());
        });
      }

      void notify() override {
        // Wait for inactivity before saving the state
        _lastChange = millis();
      }

      void loop() {
        if (_lastChange > 0) {
          // There has been a change so check for inactivity
          if (millis() - _lastChange > Config::store.getState()->light->saveStateDelay) {
            _lastChange = 0;
            Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
              JsonObject object = doc.as<JsonObject>();
              BURP_DEBUG_INFO("Document capacity: %u", doc.capacity());
              BURP_DEBUG_INFO("Document memory used: %u", doc.memoryUsage());
              Light::store.getState()->serialize(object);
              _file.write(doc);
            });
          }
        }
      }

    private:

      const Json::File _file;
      unsigned long _lastChange;

  };

  using LightFileDocumentClass = StaticJsonDocument<256>;
  extern LightFile<LightFileDocumentClass> lightFile;

}
