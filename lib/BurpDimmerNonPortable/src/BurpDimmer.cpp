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
    using Node = BurpTree::Leaf<Factory, 2>;
    Node::Subscribers subscribers = {
        &light,
        &file
    };
    Node node(Id::root, factory, subscribers);

    using Root = BurpTree::Root<Node>;
    Root root(node);

    using Dispatcher = BurpTree::Dispatcher<Node>;
    Dispatcher dispatcher(root, node);

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
    LightControls::Instance<Dispatcher> controls(dispatcher, rotaryEncoder, button);
    ConfigSubscriber<Dispatcher> configSubscriber(dispatcher);

  }

  namespace Network {

    namespace Manager {
      Instance instance;
    }

  }

  namespace Config {

    using Node = BurpTree::Branch<2, 1>;

    namespace Id {
      enum : BurpTree::Node::Id {
        light,
        networkAccessPoint,
        networkManager,
        networkStation
      };
    }

    namespace Light {
      constexpr char field[] = "light";
      Factory factory;
      using Node = BurpTree::Leaf<Factory, 1>;
      Node::Subscribers subscribers = {
          &BurpDimmer::Light::configSubscriber
      };
      Node node(Id::light, factory, subscribers);
      Config::Node::Entry entry = {field, &node};
    }

    namespace Network {

      constexpr char field[] = "network";
      using Node = BurpTree::Branch<3, 0>;

      namespace AccessPoint {
        constexpr char field[] = "accessPoint";
        Factory factory;
        using Node = BurpTree::Leaf<Factory, 0>;
        Node::Subscribers subscribers = {};
        Node node(Id::networkAccessPoint, factory, subscribers);
        Network::Node::Entry entry = {field, &node};
      }
      namespace Manager {
        constexpr char field[] = "manager";
        Factory factory;
        using Node = BurpTree::Leaf<Factory, 1>;
        Node::Subscribers subscribers = {
            &BurpDimmer::Network::Manager::instance
        };
        Node node(Id::networkManager, factory, subscribers);
        Network::Node::Entry entry = {field, &node};
      }
      namespace Station {
        constexpr char field[] = "station";
        Factory factory;
        using Node = BurpTree::Leaf<Factory, 0>;
        Node::Subscribers subscribers = {};
        Node node(Id::networkStation, factory, subscribers);
        Network::Node::Entry entry = {field, &node};
      }

      Node::Map map = {
          &AccessPoint::entry,
          &Manager::entry,
          &Station::entry
      };
      Node::Subscribers subscribers = {};
      Node node(map, subscribers);
      Config::Node::Entry entry = {field, &node};

    }

    Json::File::Instance fileInstance(filePath);
    ConfigFile::Instance<Node::State, fileSize> file(fileInstance);

    Node::Map map = {
        &Light::entry,
        &Network::entry
    };
    Node::Subscribers subscribers = {
        &file,
    };
    Node node(map, subscribers);

    using Root = BurpTree::Root<Node>;
    Root root(node);

    namespace Light {
      BurpTree::Dispatcher<Node> dispatcher(root, node);
    }

    namespace Network {
      namespace AccessPoint {
        BurpTree::Dispatcher<Node> dispatcher(root, node);
      }
      namespace Manager {
        BurpTree::Dispatcher<Node> dispatcher(root, node);
      }
      namespace Station {
        BurpTree::Dispatcher<Node> dispatcher(root, node);
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
    Config::file.read(std::bind(&Config::Root::deserialize, &Config::root, _1));
    Light::file.read(std::bind(&Light::Root::deserialize, &Light::root, _1));

    Light::controls.setup();
  }

  void loop() {
    Config::root.loop();
    Light::root.loop();
    Light::file.loop();
    Light::controls.loop();
  }

}
