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

      using f_withObj = std::function<void(const JsonObject & object)>;

      LightFile(Light::Store & store, const char * path) :
        _store(store),
        _file(path),
        _lastChange(0)
      {}

      void init(f_withObj withObj) {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          _file.read(doc);
          withObj(doc.as<JsonObject>());
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
              _store.getState()->serialize(object);
              _file.write(doc);
            });
          }
        }
      }

    private:

      Light::Store & _store;
      const Json::File _file;
      unsigned long _lastChange;

  };

  using LightFileDocumentClass = StaticJsonDocument<256>;
  extern LightFile<LightFileDocumentClass> lightFile;

}
