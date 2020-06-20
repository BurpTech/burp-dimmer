#pragma once

#include <ArduinoJson.h>
#include "Light/Store.hpp"
#include "Light/Reducer.hpp"
#include "Light/ConfigSubscriber.hpp"

namespace BurpDimmer {
  namespace Light {

      void init(Store & store, const Reducer & reducer, const JsonObject & object);
      void init(const JsonObject & object);
      extern Store store;
      extern ConfigSubscriber configSubscriber;

  }
}
