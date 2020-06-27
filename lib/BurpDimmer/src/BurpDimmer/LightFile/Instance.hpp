#pragma once

#include <BurpDebug.hpp>
#include "../Json/withDoc.hpp"
#include "../Json/File/Interface.hpp"
#include "Interface.hpp"

namespace BurpDimmer {
  namespace LightFile {

    template <size_t size>
    class Instance : public Interface {

      public:

        Instance(const Json::File::Interface & file) :
          _state(nullptr),
          _file(file),
          _lastChange(0)
        {}

        void read(f_withObj withObj) override {
          Json::withStaticDoc<size>([&](JsonDocument & doc) {
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

        void loop() override {
          if (_lastChange > 0) {
            // There has been a change so check for inactivity
            if (millis() - _lastChange > _state->config->saveStateDelay) {
              _lastChange = 0;
              Json::withStaticDoc<size>([&](JsonDocument & doc) {
                JsonObject object = doc.to<JsonObject>();
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
}
