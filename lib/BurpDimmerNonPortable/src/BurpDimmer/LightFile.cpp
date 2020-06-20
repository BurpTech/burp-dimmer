#include "LightFile.hpp"

namespace BurpDimmer {

  constexpr char lightFilePath[] = "/light.json";
  LightFile<LightFileDocumentClass> lightFile(Light::store, lightFilePath);

}
