#pragma once

#include <ArduinoJson.h>
#include "Config/Store.hpp"
#include "Config/Light/Selector.hpp"
#include "Config/Network/Selector.hpp"
#include "Config/Network/AccessPoint/Selector.hpp"
#include "Config/Network/Manager/Selector.hpp"
#include "Config/Network/Station/Selector.hpp"
#include "Config/Reducer.hpp"

namespace BurpDimmer {
  namespace Config {

      void init(Store & store, const Reducer & reducer, const JsonObject & object);
      extern Store store;
      extern Light::Selector lightSelector;
      extern Network::Selector networkSelector;
      extern Network::AccessPoint::Selector networkAccessPointSelector;
      extern Network::Manager::Selector networkManagerSelector;
      extern Network::Station::Selector networkStationSelector;

  }
}
