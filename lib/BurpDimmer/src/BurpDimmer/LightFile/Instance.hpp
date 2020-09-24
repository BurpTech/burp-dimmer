#pragma once

#include <ArduinoJson.h>
#include "../Json/File/Interface.hpp"
#include "Interface.hpp"

namespace BurpDimmer {
  namespace LightFile {

    template <size_t size>
    class Instance : public Interface {

      public:

        Instance(const Json::File::Interface & file) :
          _light(nullptr),
          _file(file),
          _lastChange(0)
        {}

        void read(f_withObj withObj) override {
          StaticJsonDocument<size> doc;
          _file.read(doc);
          withObj(doc.template as<JsonVariant>());
        }

        void setup(const Light::State * initial) override {
          // do nothing (the config read triggers setup)
        }

        void update(const Light::State * next) override {
          // Wait for inactivity before saving the state
          _lastChange = millis();
          _light = next;
        }

        void loop() override {
          if (_lastChange > 0) {
            // There has been a change so check for inactivity
            if (millis() - _lastChange > _light->saveStateDelay) {
              _lastChange = 0;
              StaticJsonDocument<size> doc;
              JsonVariant variant = doc.template to<JsonVariant>();
              _light->serialize(variant);
              _file.write(doc);
            }
          }
        }

      private:

        const Light::State * _light;
        const Json::File::Interface & _file;
        unsigned long _lastChange;

    };

  }
}
