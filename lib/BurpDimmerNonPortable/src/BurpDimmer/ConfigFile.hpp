#pragma once

#include <functional>
#include <BurpRedux/Subscriber.hpp>
#include <BurpDimmer/Json/withDoc.hpp>
#include <BurpDimmer/Config/State.hpp>
#include "Json/File.hpp"

namespace BurpDimmer {

  template <class JsonDocumentClass>
  class ConfigFile : public BurpRedux::Subscriber<Config::State::Instance> {

    public:

      using f_withObj = std::function<void(const JsonObject & object)>;

      ConfigFile(const char * path) :
        _file(path)
      {}

      void init(f_withObj withObj) {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          _file.read(doc);
          withObj(doc.as<JsonObject>());
        });
      }

      void onPublish(const Config::State::Instance * state) override {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          JsonObject object = doc.as<JsonObject>();
          state->serialize(object);
          _file.write(doc);
        });
      }

    private:

      const Json::File _file;

  };

  using ConfigFileDocumentClass = StaticJsonDocument<1024>;
  extern ConfigFile<ConfigFileDocumentClass> configFile;

}
