#pragma once

#include "../Json/withDoc.hpp"
#include "../Json/File/Interface.hpp"
#include "Interface.hpp"

namespace BurpDimmer {
  namespace ConfigFile {

    template <size_t size>
    class Instance : public Interface {

      public:

        Instance(const Json::File::Interface & file) :
          _file(file)
        {}

        void read(f_withObj withObj) override {
          Json::withDoc<size>([&](JsonDocument & doc) {
            _file.read(doc);
            withObj(doc.as<JsonObject>());
          });
        }

        void setup(const Config::State::Instance * state) override {
          // do nothing (the config read triggers setup)
        }

        void onPublish(const Config::State::Instance * state) override {
          Json::withDoc<size>([&](JsonDocument & doc) {
            JsonObject object = doc.as<JsonObject>();
            state->serialize(object);
            _file.write(doc);
          });
        }

      private:

        const Json::File::Interface & _file;

    };

  }
}
