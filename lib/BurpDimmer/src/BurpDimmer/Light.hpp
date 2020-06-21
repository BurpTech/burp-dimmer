#pragma once

#include <ArduinoJson.h>
#include "Light/Config.hpp"

namespace BurpDimmer {
  namespace Light {

      void read(const Config * config, const JsonObject & object);

  }
}
