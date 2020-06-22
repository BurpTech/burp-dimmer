#pragma once

#include <BurpDimmer/Json/File/Interface.hpp>

namespace BurpDimmer {
  namespace Json {
    namespace File {

      class Instance : public Interface {

        public:

          Instance(const char * path);
          void read(JsonDocument & doc) const override;
          void write(JsonDocument & doc) const override;
          void remove() override;

        private:

          const char * _path;

      };

    }
  }
}
