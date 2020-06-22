#include "Json/File/Instance.hpp"
#include "LightFile.hpp"

namespace BurpDimmer {

  constexpr char lightFilePath[] = "/light.json";
  const Json::File::Instance lightFileInstance(lightFilePath);
  LightFile<LightFileDocumentClass> lightFile(lightFileInstance);

}
