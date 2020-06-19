#include <Arduino.h>
#include <EEPROM.h>

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

#include <BurpDimmer/FactorySettings.hpp>
#include <BurpDimmer/ConfigFile.hpp>
#include <BurpDimmer/Config.hpp>

using namespace BurpDimmer;

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
