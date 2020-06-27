#include <Arduino.h>
#include <EEPROM.h>
#include <LittleFS.h>
#include "BurpDimmer.hpp"

#define _STR(VAL) #VAL
#define STR(VAL) _STR(VAL)

#define EEPROM_SIZE 512

#ifndef APPL_NAME
#define APPL_NAME application
#endif

#ifndef VERSION
#define VERSION development
#endif

#ifndef BAUDRATE
#define BAUDRATE 9600
#endif

#include <ArduinoJson.h>
#include <BurpDimmer/FactorySettings/Instance.hpp>
#include <BurpDimmer/Light/Store.hpp>
#include <BurpDimmer/LightFile/Instance.hpp>
#include <BurpDimmer/Light/Reducer.hpp>
#include <BurpDimmer/Light/Actions.hpp>
#include <BurpDimmer/Light/ConfigSubscriber.hpp>
#include <BurpDimmer/LightControls/Instance.hpp>
#include <BurpDimmer/Network/Manager.hpp>
#include <BurpDimmer/ConfigFile/Instance.hpp>
#include <BurpDimmer/Config/Store.hpp>
#include <BurpDimmer/Config/Light/Reducer.hpp>
#include <BurpDimmer/Config/Light/Actions.hpp>
#include <BurpDimmer/Config/Reducer.hpp>
#include <BurpDimmer/Config/Network/Reducer.hpp>
#include <BurpDimmer/Config/Network/AccessPoint/Reducer.hpp>
#include <BurpDimmer/Config/Network/AccessPoint/Actions.hpp>
#include <BurpDimmer/Config/Network/Manager/Reducer.hpp>
#include <BurpDimmer/Config/Network/Manager/Actions.hpp>
#include <BurpDimmer/Config/Network/Station/Reducer.hpp>
#include <BurpDimmer/Config/Network/Station/Actions.hpp>
#include <BurpDimmer/Json/File/Instance.hpp>
#include <BurpDimmer/Components/Light.hpp>
#include <BurpDimmer/Components/RotaryEncoder.hpp>
#include <BurpDimmer/Components/Button.hpp>
#include <BurpDimmer/Constants.hpp>

namespace BurpDimmer {

  namespace FactorySettings {
    Instance instance;
  }

  namespace Light {

    Components::Light::Instance light(pin);

    Json::File::Instance fileInstance(filePath);
    LightFile::Instance<fileSize> file(fileInstance);

    State::Creator creator;
    Reducer reducer(creator, deserialize);
    using S = Store::Instance<2>;
    S store(reducer, S::Subscribers({
        &light,
        &file
    }));

    ICACHE_RAM_ATTR void rotaryEncoderInterruptDispatch();

    Components::RotaryEncoder rotaryEncoder(
        rotaryEncoderPinA,
        rotaryEncoderPinB,
        rotaryEncoderInterruptDispatch
    );

    void rotaryEncoderInterruptDispatch() {
      rotaryEncoder.interrupt();
    }

    Components::Button button(buttonPin, buttonDebounceDelay);

    LightControls::Instance controls(store, rotaryEncoder, button);

    ConfigSubscriber configSubscriber(store);

  }

  namespace Network {

    namespace Manager {
      Instance instance;
    }

  }

  namespace Config {

    Json::File::Instance fileInstance(filePath);
    ConfigFile::Instance<fileSize> file(fileInstance);

    namespace Light {
      State::Creator creator;
      Reducer reducer(creator, deserialize);
      ReducerMapping reducerMapping(reducer);
      Selector<1> selector({
          &BurpDimmer::Light::configSubscriber
      });
    }

    namespace Network {
      namespace AccessPoint {
        State::Creator creator;
        Reducer reducer(creator, deserialize);
        ReducerMapping reducerMapping(reducer);
        Selector<0> selector({});
      }
      namespace Manager {
        State::Creator creator;
        Reducer reducer(creator, deserialize);
        ReducerMapping reducerMapping(reducer);
        Selector<1> selector({
            &BurpDimmer::Network::Manager::instance
        });
      }
      namespace Station {
        State::Creator creator;
        Reducer reducer(creator, deserialize);
        ReducerMapping reducerMapping(reducer);
        Selector<0> selector({});
      }
      State::Creator creator;
      using R  = Reducer<3>;
      R reducer(creator, R::Map{
          &AccessPoint::reducerMapping,
          &Manager::reducerMapping,
          &Station::reducerMapping
      });
      ReducerMapping reducerMapping(reducer);
      Selector<3> selector({
          &AccessPoint::selector,
          &Manager::selector,
          &Station::selector
      });
    }

    State::Creator creator;
    using R  = Reducer<2>;
    R reducer(creator, R::Map{
        &Light::reducerMapping,
        &Network::reducerMapping
    });
    using S = Store::Instance<3>;
    S store(reducer, S::Subscribers({
        &file,
        &Light::selector,
        &Network::selector
    }));

  }

  void setup() {
    // Initialise the serial output
    Serial.begin(BAUDRATE);
    
    // Report name and version
    Serial.println(STR(APPL_NAME) " : " STR(VERSION));

    // TODO: We may not be concerned about
    // real random values but should probably
    // change this seed. However at present
    // this does still generate different values
    // every time
    randomSeed(0);

    // Initialise the EEPROM library
    EEPROM.begin(EEPROM_SIZE);

    // Initialise the file system
    LittleFS.begin();

    FactorySettings::instance.setup();

    Config::file.read([](const JsonObject & object) {
        Config::State::Params params;
        Config::store.deserialize(object, params);
    });

    Light::file.read([](const JsonObject & object) {
        Light::State::Params params;
        params.config = Config::Light::selector.getState();
        Light::store.deserialize(object, params);
    });

    Light::controls.setup();
  }

  void loop() {
    Config::store.loop();
    Light::store.loop();
    Light::file.loop();
    Light::controls.loop();
  }

}
