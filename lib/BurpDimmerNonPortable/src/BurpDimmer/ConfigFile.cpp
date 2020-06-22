#include "Json/File/Instance.hpp"
#include "ConfigFile.hpp"

namespace BurpDimmer {

  constexpr char configFilePath[] = "/config.json";
  const Json::File::Instance configFileInstance(configFilePath);
  ConfigFile<ConfigFileDocumentClass> configFile(configFileInstance);

}
