#include <functional>
#include <EEPROM.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <BurpTree/Node.hpp>
#include <BurpTree/Root.hpp>
#include <BurpTree/Leaf.hpp>
#include <BurpTree/Branch.hpp>
#include <BurpTree/Dispatcher.hpp>
#include <BurpDimmer/FactorySettings/Instance.hpp>
#include <BurpDimmer/Light/State.hpp>
#include <BurpDimmer/LightFile/Instance.hpp>
#include <BurpDimmer/Light/ConfigSubscriber.hpp>
#include <BurpDimmer/LightControls/Instance.hpp>
#include <BurpDimmer/Network/Manager.hpp>
#include <BurpDimmer/ConfigFile/Instance.hpp>
#include <BurpDimmer/Config/Light/State.hpp>
#include <BurpDimmer/Config/Network/AccessPoint/State.hpp>
#include <BurpDimmer/Config/Network/Manager/State.hpp>
#include <BurpDimmer/Config/Network/Station/State.hpp>
#include <BurpDimmer/Json/File/Instance.hpp>
#include <BurpDimmer/Components/Light.hpp>
#include <BurpDimmer/Components/RotaryEncoder.hpp>
#include <BurpDimmer/Components/Button.hpp>
#include <BurpDimmer/Constants.hpp>
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

namespace BurpDimmer {

  namespace FactorySettings {
    Instance instance;
  }

  namespace Light {

    namespace Id {
      enum : BurpTree::Node::Id {
        root
      };
    }

    Components::Light::Instance light(pin);

    Json::File::Instance fileInstance(filePath);
    LightFile::Instance<fileSize> file(fileInstance);

    Factory factory;
    using Node = BurpTree::Leaf<2>;
    Node node(Id::root, factory, Node::Subscribers({
        &light,
        &file
    }));

    BurpTree::Root root(node);
    BurpTree::Dispatcher<Factory> dispatcher(root, Id::root, factory);

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
    LightControls::Instance controls(dispatcher, rotaryEncoder, button);
    ConfigSubscriber configSubscriber(dispatcher, factory);

  }

  namespace Network {

    namespace Manager {
      Instance instance;
    }

  }

  namespace Config {

    Json::File::Instance fileInstance(filePath);
    ConfigFile::Instance<fileSize> file(fileInstance);

    namespace Id {
      enum : BurpTree::Node::Id {
        light,
        networkAccessPoint,
        networkManager,
        networkStation
      };
    }

    namespace Light {
      Factory factory;
      using Node = BurpTree::Leaf<1>;
      Node node(Id::light, factory, Node::Subscribers({
          &BurpDimmer::Light::configSubscriber
      }));
    }

    namespace Network {

      namespace AccessPoint {
        Factory factory;
        using Node = BurpTree::Leaf<0>;
        Node node(Id::networkAccessPoint, factory, Node::Subscribers({
        }));
      }
      namespace Manager {
        Factory factory;
        using Node = BurpTree::Leaf<1>;
        Node node(Id::networkManager, factory, Node::Subscribers({
            &BurpDimmer::Network::Manager::instance
        }));
      }
      namespace Station {
        Factory factory;
        using Node = BurpTree::Leaf<0>;
        Node node(Id::networkStation, factory, Node::Subscribers({
        }));
      }

      constexpr char accessPointField[] = "accessPoint";
      constexpr char managerField[] = "manager";
      constexpr char stationField[] = "station";

      using Node = BurpTree::Branch<3, 0>;
      Node node(Node::Map({
          Node::Entry({accessPointField, &AccessPoint::node}),
          Node::Entry({managerField, &Manager::node}),
          Node::Entry({stationField, &Station::node})
      }), Node::Subscribers({
      }));

    }

    constexpr char lightField[] = "light";
    constexpr char networkField[] = "network";

    using Node = BurpTree::Branch<2, 1>;
    Node node(Node::Map({
        Node::Entry({lightField, &Light::node}),
        Node::Entry({networkField, &Network::node})
    }), Node::Subscribers({
        &file,
    }));

    BurpTree::Root root(node);

    namespace Light {
      BurpTree::Dispatcher<Factory> dispatcher(root, Id::light, factory);
    }

    namespace Network {
      namespace AccessPoint {
        BurpTree::Dispatcher<Factory> dispatcher(root, Id::networkAccessPoint, factory);
      }
      namespace Manager {
        BurpTree::Dispatcher<Factory> dispatcher(root, Id::networkManager, factory);
      }
      namespace Station {
        BurpTree::Dispatcher<Factory> dispatcher(root, Id::networkStation, factory);
      }
    }

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

    using namespace std::placeholders;
    Config::file.read(std::bind(&BurpTree::Root::deserialize, &Config::root, _1));
    Light::file.read(std::bind(&BurpTree::Root::deserialize, &Light::root, _1));

    Light::controls.setup();
  }

  void loop() {
    Config::root.loop();
    Light::root.loop();
    Light::file.loop();
    Light::controls.loop();
  }

}
