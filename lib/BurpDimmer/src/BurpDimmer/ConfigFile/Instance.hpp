#pragma once

#include <stddef.h>
#include <Redux/Subscriber.hpp>
#include <Json/File.hpp>
#include <Json/withDoc.hpp>
#include <Config.hpp>

namespace BurpDimmer {
  namespace ConfigFile {

    template <class JsonDocumentClass>
    class Instance : public Redux::Subscriber {

      public:

        Instance(const char * path) :
          _file(path),
          _store(nullptr)
        {}

        void init(Config::Store * store) {
          _store = store;
          Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
            _file.read(doc);
            _store->init(doc.as<JsonObject>());
          });
        }

        void notify() override {
          Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
            JsonObject object = doc.as<JsonObject>();
            _store->getState()->serialize(object);
            _file.write(doc);
          });
        }

      private:

        const Json::File _file;
        Config::Store * _store;

    };

  }
}
