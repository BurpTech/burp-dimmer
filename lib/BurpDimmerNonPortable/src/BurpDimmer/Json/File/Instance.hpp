#pragma once

#include <BurpLogger.hpp>
#include <BurpDimmer/Json/File/Interface.hpp>

namespace BurpDimmer {
  namespace Json {
    namespace File {

      class Instance : public Interface {

        public:

          Instance(const BurpLogger::Logger * logger, const char * path);
          void read(JsonDocument & doc) const override;
          void write(JsonDocument & doc) const override;
          void remove() override;

        private:

          const BurpLogger::Logger * _logger;
          const char * _path;

      };

    }
  }
}
