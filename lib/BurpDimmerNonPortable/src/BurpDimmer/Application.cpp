#include <ArduinoJson.h>
#include <BurpDimmer/FactorySettings/Instance.hpp>
#include <BurpDimmer/Light/Store.hpp>
#include <BurpDimmer/LightFile/Instance.hpp>
#include <BurpDimmer/Light/Deserialize.hpp>
#include <BurpDimmer/Light/Reducer.hpp>
#include <BurpDimmer/Light/ConfigSubscriber.hpp>
#include <BurpDimmer/LightControls/Instance.hpp>
#include <BurpDimmer/Network/Manager.hpp>
#include <BurpDimmer/ConfigFile/Instance.hpp>
#include <BurpDimmer/Config/Store.hpp>
#include <BurpDimmer/Config/Deserialize.hpp>
#include <BurpDimmer/Config/Reducer.hpp>
#include <BurpDimmer/Config/Network/Reducer.hpp>
#include <BurpDimmer/Config/Network/AccessPoint/Reducer.hpp>
#include <BurpDimmer/Config/Network/Manager/Reducer.hpp>
#include <BurpDimmer/Config/Network/Station/Reducer.hpp>
#include <BurpDimmer/Json/File/Instance.hpp>
#include <BurpDimmer/Components/Light.hpp>
#include <BurpDimmer/Components/RotaryEncoder.hpp>
#include <BurpDimmer/Components/Button.hpp>
#include "Constants.hpp"
#include "Application.hpp"

namespace BurpDimmer {
  namespace Application {

    namespace FactorySettings {
      Instance instance;
    }

    namespace Light {

      using namespace BurpDimmer::Light;
      using namespace Constants::Light;

      Components::Light::Instance light(pin);

      Json::File::Instance fileInstance(filePath);
      LightFile::Instance<fileSize> file(fileInstance);

      State::Creator creator;
      Reducer reducer(creator);
      using Store = Store::Instance<2>;
      Store store(reducer, Store::Subscribers({
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

      Components::Button button(buttonPin, Constants::buttonDebounceDelay);

      LightControls::Instance controls(store, rotaryEncoder, button);

      ConfigSubscriber configSubscriber(store);

    }

    namespace Network {

      using namespace BurpDimmer::Network;

      namespace Manager {
        Instance instance;
      }

    }

    namespace Config {

      using namespace BurpDimmer::Config;
      using namespace Constants::Config;

      Json::File::Instance fileInstance(filePath);
      ConfigFile::Instance<fileSize> file(fileInstance);

      namespace Light {
        State::Creator creator;
        Reducer reducer(creator);
        ReducerMapping reducerMapping(reducer);
        Selector<1> selector({
            &Application::Light::configSubscriber
        });
      }

      namespace Network {
        namespace AccessPoint {
          State::Creator creator;
          Reducer reducer(creator);
          ReducerMapping reducerMapping(reducer);
          Selector<0> selector({});
        }
        namespace Manager {
          State::Creator creator;
          Reducer reducer(creator);
          ReducerMapping reducerMapping(reducer);
          Selector<1> selector({
              &Application::Network::Manager::instance
          });
        }
        namespace Station {
          State::Creator creator;
          Reducer reducer(creator);
          ReducerMapping reducerMapping(reducer);
          Selector<0> selector({});
        }
        State::Creator creator;
        using Reducer  = Reducer<3>;
        Reducer reducer(creator, Reducer::Map{
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
      using Reducer  = Reducer<2>;
      Reducer reducer(creator, Reducer::Map{
          &Light::reducerMapping,
          &Network::reducerMapping
      });
      using Store = Store::Instance<3>;
      Store store(reducer, Store::Subscribers({
          &configFile,
          &Light::selector,
          &Network::selector
      }));

    }

    void setup() {
      FactorySettings::instance.setup();

      Config::file.read([](const JsonObject & object) {
          BurpDimmer::Config::deserialize(object, [](const BurpDimmer::Config::State::Instance * state) {
              Config::store.setup(state);
          });
      });

      Light::file.read([](const JsonObject & object) {
          BurpDimmer::Light::deserialize(object, Config::Light::selector.getState(), [](const BurpDimmer::Config::State::Instance * state) {
              Light::store.setup(state);
          });
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
}
