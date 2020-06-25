#pragma once

#include <functional>
#include <BurpRedux/Subscriber/Interface.hpp>
#include <BurpDimmer/Json/withDoc.hpp>
#include <BurpDimmer/Config/State.hpp>
#include "Json/File/Interface.hpp"

namespace BurpDimmer {

  template <class JsonDocumentClass>
  class ConfigFile : public BurpRedux::Subscriber::Interface<Config::State::Instance> {

    public:

      using f_withObj = std::function<void(const JsonObject & object)>;

      ConfigFile(const Json::File::Interface & file) :
        _file(file)
      {}

      void read(f_withObj withObj) {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          _file.read(doc);
          withObj(doc.as<JsonObject>());
        });
      }

      void setup(const Config::State::Instance * state) override {
        // do nothing (the config read triggers setup)
      }

      void onPublish(const Config::State::Instance * state) override {
        Json::withDoc<JsonDocumentClass>([&](JsonDocument & doc) {
          JsonObject object = doc.as<JsonObject>();
          state->serialize(object);
          _file.write(doc);
        });
      }

    private:

      const Json::File::Interface & _file;

  };

}
