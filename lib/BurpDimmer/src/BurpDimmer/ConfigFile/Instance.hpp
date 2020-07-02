#pragma once

#include "../Json/withDoc.hpp"
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
          Json::withStaticDoc<size>([&](JsonDocument & doc) {
            _file.read(doc);
            withObj(doc.as<JsonObject>());
          });
        }

        void setup(const Config * initial) override {
          // do nothing (the config read triggers setup)
        }

        void update(const Config * next) override {
          Json::withStaticDoc<size>([&](JsonDocument & doc) {
            JsonObject object = doc.to<JsonObject>();
            next->serialize(object);
            _file.write(doc);
          });
        }

      private:

        const Json::File::Interface & _file;

    };

  }
}
