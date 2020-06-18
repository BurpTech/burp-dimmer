#include "ConfigFile.hpp"

namespace BurpDimmer {
  namespace ConfigFile {

    constexpr char path[] = "/config.json";
    Instance<StaticJsonDocument<jsonDocumentSize>> instance(path);

  }
}
