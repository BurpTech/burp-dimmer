#include <functional>
#include <CppRedux/SubscriberList.hpp>
#include <BurpDimmer/Config.hpp>
#include <BurpDimmer/Light.hpp>
#include <BurpDimmer/Light/ConfigSubscriber.hpp>
#include "BurpDimmer/FactorySettings.hpp"
#include "BurpDimmer/Storage.hpp"
#include "BurpDimmer/ConfigFile.hpp"
#include "BurpDimmer/LightFile.hpp"
#include "BurpDimmer/Components/Light.hpp"
#include "BurpDimmer/LightControls.hpp"
#include "BurpDimmer/Network.hpp"
#include "BurpDimmer/defines.hpp"
#include "BurpDimmer.hpp"

namespace BurpDimmer {

  using namespace std::placeholders;

  Components::Light light(BURP_DIMMER_LIGHT_PIN, Light::store);

  CppRedux::Subscribers<3> configSubscribers = {
    &configFile,
    &Config::lightSelector,
    &Config::networkSelector
  };
  CppRedux::SubscriberList<3> configSubscriberList(configSubscribers);

  CppRedux::Subscribers<3> configNetworkSubscribers = {
    &Config::networkAccessPointSelector,
    &Config::networkManagerSelector,
    &Config::networkStationSelector
  };
  CppRedux::SubscriberList<3> configNetworkSubscriberList(configNetworkSubscribers);

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
    configFile.init([](const JsonObject & obj) {
        Config::init(Config::store, Config::reducer, obj);
    });

    // load the light state from the light file
    lightFile.init([](const JsonObject & obj) {
        Light::init(Light::store, Light::reducer, obj);
    });
    
    // setup the light as soon as we can
    light.setup();
    
    // set the config subscribers
    Config::store.setSubscriber(&configSubscriberList);
    Config::lightSelector.setSubscriber(&Light::configSubscriber);
    Config::networkSelector.setSubscriber(&configNetworkSubscriberList);
    Config::networkManagerSelector.setSubscriber(&Network::manager);

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