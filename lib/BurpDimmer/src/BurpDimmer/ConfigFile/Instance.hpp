#pragma once

#include <ArduinoJson.h>
#include "../Json/File/Interface.hpp"
#include "Interface.hpp"

namespace BurpDimmer {
  namespace ConfigFile {

    template <class Config, size_t size>
    class Instance : public Interface<Config> {

      public:

        Instance(const Json::File::Interface & file) :
          _file(file)
        {}

        void read(f_withObj withObj) override {
          StaticJsonDocument<size> doc;
          _file.read(doc);
          withObj(doc.template as<JsonObject>());
        }

        void setup(const Config * initial) override {
          // do nothing (the config read triggers setup)
        }

        void update(const Config * next) override {
          StaticJsonDocument<size> doc;
          JsonObject object = doc.template to<JsonObject>();
          next->serialize(object);
          _file.write(doc);
        }

      private:

        const Json::File::Interface & _file;

    };

  }
}
