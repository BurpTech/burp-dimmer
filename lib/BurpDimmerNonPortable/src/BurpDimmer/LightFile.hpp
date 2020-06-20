#pragma once

#include <functional>
#include <CppRedux/Subscriber.hpp>
#include <BurpDimmer/Json/withDoc.hpp>
#include <BurpDimmer/Light.hpp>
#include "Json/File.hpp"

namespace BurpDimmer {

  template <class JsonDocumentClass>
  class LightFile : public CppRedux::Subscriber {

    public:

      LightFile(const char * path) :
        _file(path)
      {}

      void init() {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          _file.read(doc);
          Light::init(doc.as<JsonObject>());
        });
      }

      void notify() override {
        // TODO: serialize the file occasionally not on every change
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          JsonObject object = doc.as<JsonObject>();
          Light::store.getState()->serialize(object);
          _file.write(doc);
        });
      }

    private:

      const Json::File _file;

  };

  using LightFileDocumentClass = StaticJsonDocument<1024>;
  extern LightFile<LightFileDocumentClass> lightFile;

}
