#pragma once

#include "Json/File/Interface.hpp"
#include <functional>
#include <BurpDebug.hpp>
#include <BurpRedux/Subscriber/Interface.hpp>
#include <BurpDimmer/Json/withDoc.hpp>
#include <BurpDimmer/Light/State.hpp>
#include "Json/File/Interface.hpp"

namespace BurpDimmer {

  template <class JsonDocumentClass>
  class LightFile : public BurpRedux::Subscriber::Interface<Light::State::Instance> {

    public:

      using f_withObj = std::function<void(const JsonObject & object)>;

      LightFile(const Json::File::Interface & file) :
        _state(nullptr),
        _file(file),
        _lastChange(0)
      {}

      void read(f_withObj withObj) {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          _file.read(doc);
          withObj(doc.as<JsonObject>());
        });
      }

      void setup(const Light::State::Instance * state) override {
        // do nothing (the config read triggers setup)
      }

      void onPublish(const Light::State::Instance * state) override {
        // Wait for inactivity before saving the state
        _lastChange = millis();
        _state = state;
      }

      void loop() {
        if (_lastChange > 0) {
          // There has been a change so check for inactivity
          if (millis() - _lastChange > _state->config->saveStateDelay) {
            _lastChange = 0;
            Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
              JsonObject object = doc.as<JsonObject>();
              BURP_DEBUG_INFO("Document capacity: %u", doc.capacity());
              BURP_DEBUG_INFO("Document memory used: %u", doc.memoryUsage());
              _state->serialize(object);
              _file.write(doc);
            });
          }
        }
      }

    private:

      const Light::State::Instance * _state;
      const Json::File::Interface & _file;
      unsigned long _lastChange;

  };

}
