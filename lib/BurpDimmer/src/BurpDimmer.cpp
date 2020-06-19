#include "BurpDimmer.hpp"

#include "BurpDimmer/FactorySettings.hpp"
#include "BurpDimmer/ConfigFile.hpp"
#include "BurpDimmer/Config.hpp"

namespace BurpDimmer {

  void setup() {
    // Initialise the factory settings
    FactorySettings::instance.init();
    
    // Load the config state from the config file
    configFile.init();

    // The config file instance should subscribe to config
    // state changes so that they will be saved
    Config::store.setSubscriber(&configFile);
  }

  void loop() {
    // loop the config redux store to notify subscribers
    Config::store.loop();
  }

}
