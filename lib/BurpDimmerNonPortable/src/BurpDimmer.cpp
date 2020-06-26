#include <Arduino.h>
#include <EEPROM.h>
#include <LittleFS.h>
#include "BurpDimmer/Application.hpp"

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

    // setup the application
    Application::setup();
  }

  void loop() {
    // loop the application
    Application::loop();
  }

}
