#include <functional>
#include <BurpDimmer/Config.hpp>
#include <BurpDimmer/Config/Store.hpp>
#include <BurpDimmer/Config/Light/Selector.hpp>
#include <BurpDimmer/Config/Network/Manager/Selector.hpp>
#include <BurpDimmer/Light.hpp>
#include <BurpDimmer/Light/Store.hpp>
#include <BurpDimmer/Light/ConfigSubscriber.hpp>
#include <BurpDimmer/Json/File/Instance.hpp>
#include <BurpDimmer/ConfigFile.hpp>
#include <BurpDimmer/LightFile.hpp>
#include "BurpDimmer/FactorySettings.hpp"
#include "BurpDimmer/Storage.hpp"
#include "BurpDimmer/Components/Light.hpp"
#include "BurpDimmer/LightControls.hpp"
#include "BurpDimmer/Network.hpp"
#include "BurpDimmer/defines.hpp"
#include "BurpDimmer.hpp"

namespace BurpDimmer {

  using namespace std::placeholders;

  Components::Light::Instance light(BURP_DIMMER_LIGHT_PIN);

  constexpr char configFilePath[] = "/config.json";
  const Json::File::Instance configFileInstance(configFilePath);
  ConfigFile<StaticJsonDocument<1024>> configFile(configFileInstance);

  constexpr char lightFilePath[] = "/light.json";
  const Json::File::Instance lightFileInstance(lightFilePath);
  LightFile<StaticJsonDocument<256>> lightFile(lightFileInstance);

  void setup() {
    // Initialise the factory settings
    FactorySettings::instance.init();

    // Initialise the file system
    Storage::begin();

    // Load the config state from the config file
    configFile.read(Config::read);
    Config::store.subscribe(&configFile);
    Config::Light::selector.subscribe(&Light::configSubscriber);

    // load the light state from the light file
    lightFile.read([](const JsonObject & obj) {
        Light::read(Config::Light::selector.getState(), obj);
    });
    Light::store.subscribe(&lightFile);
    
    // setup the light as soon as we can
    light.setup(Light::store.getState());
    Light::store.subscribe(&light);

    // initialize the network manager
    Network::Manager::setup(Config::Network::Manager::selector.getState());
    Config::Network::Manager::selector.subscribe(&Network::Manager::instance);
    
    // setup the light controls
    LightControls::setup();

    // Report the number of subscribers actually used
    Config::reportSubscriberCounts();
    Light::reportSubscriberCounts();
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
