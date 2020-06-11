#include "ConfigFile.hpp"

namespace ConfigFile {

  constexpr char path[] = "/config.json";
  Instance<StaticJsonDocument<jsonDocumentSize>> instance(path);

}
