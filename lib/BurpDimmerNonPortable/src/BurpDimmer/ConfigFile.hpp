#pragma once

#include <functional>
#include <CppRedux/Subscriber.hpp>
#include <BurpDimmer/Json/withDoc.hpp>
#include <BurpDimmer/Config.hpp>
#include "Json/File.hpp"

namespace BurpDimmer {

  template <class JsonDocumentClass>
  class ConfigFile : public CppRedux::Subscriber {

    public:

      using f_withObj = std::function<void(const JsonObject & object)>;

      ConfigFile(Config::Store & store, const char * path) :
        _store(store),
        _file(path)
      {}

      void init(f_withObj withObj) {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          _file.read(doc);
          withObj(doc.as<JsonObject>());
        });
      }

      void notify() override {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          JsonObject object = doc.as<JsonObject>();
          _store.getState()->serialize(object);
          _file.write(doc);
        });
      }

    private:

      Config::Store & _store;
      const Json::File _file;

  };

  using ConfigFileDocumentClass = StaticJsonDocument<1024>;
  extern ConfigFile<ConfigFileDocumentClass> configFile;

}
