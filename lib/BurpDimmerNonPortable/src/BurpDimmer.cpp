#include <CppRedux/SubscriberList.hpp>
#include <BurpDimmer/Config.hpp>
#include <BurpDimmer/Light.hpp>
#include <BurpDimmer/Light/Subscriber.hpp>
#include "BurpDimmer/FactorySettings.hpp"
#include "BurpDimmer/Storage.hpp"
#include "BurpDimmer/ConfigFile.hpp"
#include "BurpDimmer/LightFile.hpp"
#include "BurpDimmer/Components/Light.hpp"
#include "BurpDimmer/LightControls.hpp"
#include "BurpDimmer/defines.hpp"
#include "BurpDimmer.hpp"

namespace BurpDimmer {

  Components::Light light(BURP_DIMMER_LIGHT_PIN);

  CppRedux::Subscribers<2> configSubscribers = {
    // The config file instance should subscribe to config
    // state changes so that they will be saved
    &configFile,
    // The light store should be linked to the light config
    // so that changes in levels will be applied
    &Light::subscriber
  };
  CppRedux::SubscriberList<2> configSubscriberList(configSubscribers);

  CppRedux::Subscribers<2> lightSubscribers = {
    &light,
    &lightFile
  };
  CppRedux::SubscriberList<2> lightSubscriberList(lightSubscribers);

  void setup() {
    // Initialise the factory settings
    FactorySettings::instance.init();

    // Initialise the file system
    Storage::begin();

    // Load the config state from the config file
    configFile.init();

    // load the light state from the light file
    lightFile.init();
    
    // setup the light as soon as we can
    light.setup();
    
    // set the config subscribers
    Config::store.setSubscriber(&configSubscriberList);

    // set the light subscribers
    Light::store.setSubscriber(&lightSubscriberList);

    // setup the light controls
    LightControls::setup();
  }

  void loop() {
    // loop the redux stores to notify subscribers
    Light::store.loop();
    Config::store.loop();

    // loop the light controls
    LightControls::loop();

    // loop the lightFile for delayed saves
    lightFile.loop();
  }

}
