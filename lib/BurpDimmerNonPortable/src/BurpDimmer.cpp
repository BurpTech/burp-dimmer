#include <functional>
#include <EEPROM.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <BurpLogger.hpp>
#include <BurpTree/Node.hpp>
#include <BurpTree/Root.hpp>
#include <BurpTree/Leaf.hpp>
#include <BurpTree/Branch.hpp>
#include <BurpTree/Updater.hpp>
#include <BurpDimmer/FactorySettings/Instance.hpp>
#include <BurpDimmer/Light/Factory.hpp>
#include <BurpDimmer/LightFile/Instance.hpp>
#include <BurpDimmer/Light/ConfigSubscriber.hpp>
#include <BurpDimmer/LightControls/Instance.hpp>
#include <BurpDimmer/DeviceControls/Instance.hpp>
#include <BurpDimmer/Network/AccessPoint.hpp>
#include <BurpDimmer/Network/Manager.hpp>
#include <BurpDimmer/Network/Station.hpp>
#include <BurpDimmer/ConfigFile/Instance.hpp>
#include <BurpDimmer/Config/Light/Factory.hpp>
#include <BurpDimmer/Config/Network/AccessPoint/Factory.hpp>
#include <BurpDimmer/Config/Network/Manager/Factory.hpp>
#include <BurpDimmer/Config/Network/Station/Factory.hpp>
#include <BurpDimmer/Json/File/Instance.hpp>
#include <BurpDimmer/Components/Light.hpp>
#include <BurpDimmer/Components/RotaryEncoder.hpp>
#include <BurpDimmer/Components/Blinker.hpp>
#include <BurpDimmer/Components/Button.hpp>
#include <BurpDimmer/Reset/Instance.hpp>
#include <BurpDimmer/Constants.hpp>
#include "BurpDimmer.hpp"

#define _STR(VAL) #VAL
#define STR(VAL) _STR(VAL)

#define EEPROM_SIZE 512

#ifndef BURP_APPL_NAME
#define BURP_APPL_NAME application
#endif

#ifndef BURP_VERSION
#define BURP_VERSION development
#endif

#ifndef BURP_BAUDRATE
#define BURP_BAUDRATE 9600
#endif

#ifndef BURP_LOG_LEVEL
#define BURP_LOG_LEVEL BurpLogger::Level::silly
#endif

namespace BurpDimmer {

  constexpr size_t loggerMessageSize = 256;
  constexpr size_t loggerTransportCount = 1;
  constexpr size_t loggerCount = 11;

  using LoggerFactory = BurpLogger::Factory<loggerMessageSize, loggerTransportCount, loggerCount>;
  BurpLogger::Transport::Console loggerTransportConsole;
  const LoggerFactory::Transports loggerTransports = {
    &loggerTransportConsole
  };
  LoggerFactory loggerFactory(static_cast<BurpLogger::Level::Level>(BURP_LOG_LEVEL), loggerTransports);
  const BurpLogger::Logger * logger = loggerFactory.create(STR(BURP_APPL_NAME));
    
  namespace FactorySettings {
    Instance instance(logger->create("FactorySettings"));
  }

  namespace Light {

    namespace Id {
      enum : BurpTree::Node::Id {
        root
      };
    }

    Components::Light::Instance light(logger->create("light"), pin);

    Json::File::Instance fileInstance(logger->create("lightFile"), filePath);
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

    using Updater = BurpTree::Updater<Node>;
    Updater updater(root, node);

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
    LightControls::Instance<Updater> controls(logger->create("lightControls"), updater, rotaryEncoder, button);
    ConfigSubscriber<Updater> configSubscriber(logger->create("configSubscriber"), updater);

  }

  namespace Network {

    namespace AccessPoint {
      Instance instance(logger->create("networkAccessPoint"));
    }

    namespace Manager {
      Instance instance(logger->create("networkManager"));
    }

    namespace Station {
      Instance instance(logger->create("networkStation"));
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
        using Node = BurpTree::Leaf<Factory, 1>;
        Node::Subscribers subscribers = {
          &BurpDimmer::Network::AccessPoint::instance
        };
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
        using Node = BurpTree::Leaf<Factory, 1>;
        Node::Subscribers subscribers = {
          &BurpDimmer::Network::Station::instance
        };
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

    Json::File::Instance fileInstance(logger->create("configFile"), filePath);
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
      BurpTree::Updater<Node> updater(root, node);
    }

    namespace Network {
      namespace AccessPoint {
        using Updater = BurpTree::Updater<Node>;
        Updater updater(root, node);
      }
      namespace Manager {
        using Updater = BurpTree::Updater<Node>;
        Updater updater(root, node);
      }
      namespace Station {
        using Updater = BurpTree::Updater<Node>;
        Updater updater(root, node);
      }
    }

  }

  Components::Blinker blinker(blinkerPin, blinkerOn);
  Components::Button button(buttonPin, buttonDebounceDelay);
  using Reset2 = Reset::Instance<2>;
  const Reset2::Files toDelete = {
    &Config::fileInstance,
    &Light::fileInstance
  };
  const Reset2 reset(toDelete);
  DeviceControls::Instance<Config::Network::Manager::Updater> controls(
    logger->create("configControls"),
    Config::Network::Manager::updater,
    reset,
    Config::Network::Manager::node,
    blinker,
    blinkTime,
    button,
    shortDelay,
    longDelay
  );

  void setup() {
    // Initialise the serial output
    Serial.begin(BURP_BAUDRATE);
    
    // Report version
    logger->always("version : " STR(BURP_VERSION));

    // Report the actual number of loggers
    const size_t loggerCount = loggerFactory.getCount();
    const size_t loggerRequestedCount = loggerFactory.getRequestedCount();
    logger->always("logger max exceeded : %s", loggerRequestedCount > loggerCount ? "TRUE" : "FALSE");
    logger->always("logger count : " BURP_SIZE_T_FORMAT, loggerCount);
    logger->always("logger requested count : " BURP_SIZE_T_FORMAT, loggerRequestedCount);

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
    Config::Network::AccessPoint::factory.setDefaults(
      FactorySettings::instance.getSsid(),
      FactorySettings::instance.getPassphrase()
    );
    Config::Network::Station::factory.setDefaultHostname(
      FactorySettings::instance.getHostname()
    );

    using namespace std::placeholders;
    Config::file.read(std::bind(&Config::Root::setup, &Config::root, _1));
    Light::file.read(std::bind(&Light::Root::setup, &Light::root, _1));

    Light::controls.setup();
    controls.setup();
  }

  void loop() {
    Config::root.loop();
    Light::root.loop();
    Light::file.loop();
    Light::controls.loop();
    controls.loop();
  }

}
