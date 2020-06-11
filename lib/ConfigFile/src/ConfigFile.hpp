#pragma once

#include "ConfigFile/Instance.hpp"

namespace ConfigFile {

  constexpr size_t jsonDocumentSize = 1024;
  extern Instance<StaticJsonDocument<jsonDocumentSize>> instance;

}
