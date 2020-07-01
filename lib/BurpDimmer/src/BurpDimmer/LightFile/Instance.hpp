#pragma once

#include <BurpDebug.hpp>
#include "../Json/withDoc.hpp"
#include "../Json/File/Interface.hpp"
#include "../Light/State.hpp"
#include "Interface.hpp"

namespace BurpDimmer {
  namespace LightFile {

    template <size_t size>
    class Instance : public Interface {

      public:

        using State = Light::State;

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

        void setup(const BurpTree::State * initial) override {
          // do nothing (the config read triggers setup)
        }

        void onPublish(const BurpTree::State * next) override {
          // Wait for inactivity before saving the state
          _lastChange = millis();
          _state = next->as<State>();
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

        const State * _state;
        const Json::File::Interface & _file;
        unsigned long _lastChange;

    };

  }
}
