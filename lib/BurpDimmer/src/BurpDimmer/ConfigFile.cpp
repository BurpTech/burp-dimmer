#include "Instance.hpp"

namespace BurpDimmer {

  constexpr char configFilePath[] = "/config.json";
  ConfigFile<ConfigFileDocumentClass> configFile(configFilePath);

}
