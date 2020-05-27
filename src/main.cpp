#include <Arduino.h>
#include <EEPROM.h>
#include <functional>

#ifndef APPL_NAME
#define APPL_NAME application
#endif

#ifndef VERSION
#define VERSION development
#endif

#ifndef BAUDRATE
#define BAUDRATE 9600
#endif

#include "Debug.hpp"

#include "FactorySettings.hpp"
#include "Button.hpp"
#include "RotaryEncoder.hpp"
#include "Blinker.hpp"
#include "Light.hpp"
#include "Storage.hpp"
#include "HttpServer.hpp"

#include "Wifi/Config.hpp"
#include "Wifi/Ap.hpp"
#include "Wifi/Station.hpp"

#include "Json/Allocator.hpp"
#include "Json/File.hpp"
#include "Json/Object.hpp"
#include "Json/Config.hpp"
#include "Json/HttpApi.hpp"

#define EEPROM_SIZE 512
#define CONFIG_FILE_PATH "/config.json"
#define HTTP_API_PREFIX "/api/"
#define RESET_DELAY 1000
#define BUTTON_DEBOUNCE_DELAY 50

#define BLINK_LENGTH 200

namespace Blinks {
  enum {
    QUERY = 1,
    ACCESS_POINT,
    WPS_CONFIG,
    WIFI,
    FACTORY_RESTORE,
  };
};

namespace ResetLongPress {
  enum {
    RESET = 0,
    QUERY = 2000,
    ACCESS_POINT = 3000,
    WPS_CONFIG = 3000,
    WIFI = 3000,
    FACTORY_RESTORE = 3000
  };
};

#define _STR(VAL) #VAL
#define STR(VAL) _STR(VAL)

bool setupComplete = false;
void saveConfig();

void lightOnUpdate(bool on, int brightness);
Light light(D1, lightOnUpdate);

Blinker statusLight(D4, LOW);

void buttonOnRelease();
Button button(D7, BUTTON_DEBOUNCE_DELAY, buttonOnRelease);

void flashStatus(unsigned int count);
void reset();
const Button::LongPress resetLongPress = {
  ResetLongPress::RESET,
  NULL,
  reset
};
void queryNetworkMode();
const Button::LongPress resetQueryLongPress = {
  ResetLongPress::QUERY,
  std::bind(&flashStatus, Blinks::QUERY),
  queryNetworkMode
};
void toggleAccessPointMode();
const Button::LongPress resetAccessPointLongPress = {
  ResetLongPress::ACCESS_POINT,
  std::bind(&flashStatus, Blinks::ACCESS_POINT),
  toggleAccessPointMode
};
void startWpsConfig();
const Button::LongPress resetWpsConfigLongPress = {
  ResetLongPress::WPS_CONFIG,
  std::bind(&flashStatus, Blinks::WPS_CONFIG),
  startWpsConfig
};
void toggleWifi();
const Button::LongPress resetWifiLongPress = {
  ResetLongPress::WIFI,
  std::bind(&flashStatus, Blinks::WIFI),
  toggleWifi
};
void restoreFactorySettings();
const Button::LongPress resetRestoreLongPress = {
  ResetLongPress::FACTORY_RESTORE,
  []() {
    flashStatus(Blinks::FACTORY_RESTORE);
    restoreFactorySettings();
  },
  NULL
};
const Button::LongPress * resetButtonLongPresses[] = {
  &resetLongPress,
  &resetQueryLongPress,
  &resetAccessPointLongPress,
  &resetWpsConfigLongPress,
  &resetWifiLongPress,
  &resetRestoreLongPress,
  NULL
};
Button resetButton(D2, BUTTON_DEBOUNCE_DELAY, resetButtonLongPresses);

ICACHE_RAM_ATTR void knobInterruptDispatch();
void knobOnChange(int direction);
RotaryEncoder knob(D5, D6, knobInterruptDispatch, knobOnChange);

void apOnStateChange(Wifi::Ap::State state);
void stationOnStateChange(Wifi::Station::State state);
void httpServerOnSettings(const char *ssid, const char *password);

Wifi::Config apConfig(
  WIFI_AP_CONFIG_SECTION,
  []() {
    Wifi::Ap::setConfig(apConfig.ssid, apConfig.password);
    saveConfig();
  }
);

Wifi::Config stationConfig(
  WIFI_STATION_CONFIG_SECTION,
  []() {
    Wifi::Station::setConfig(stationConfig.ssid, stationConfig.password);
    saveConfig();
  }
);

Json::File configFile(CONFIG_FILE_PATH);
Json::Object *configSections[] = {
  &stationConfig,
  &apConfig,
  NULL,
};
Json::Config config(
  Json::Allocator<StaticJsonDocument<256>>::withDoc,
  configSections,
  &configFile
);
Json::HttpApi api(
  HTTP_API_PREFIX,
  Json::Allocator<StaticJsonDocument<256>>::withDoc,
  configSections,
  &HttpServer::server
);

void setup() {
  Serial.begin(BAUDRATE);
  // TODO: We may not be concerned about
  // real random values but should probably
  // change this seed. However at present
  // this does still generate different values
  // every time
  Serial.println(STR(APPL_NAME) " : " STR(VERSION));
  randomSeed(0);
  EEPROM.begin(EEPROM_SIZE);
  FactorySettings::initialize();
  apConfig.setDefaults(FactorySettings::values.ssid, FactorySettings::values.password);
  Storage::begin();
  resetButton.setup();
  statusLight.setup();
  light.setup();
  button.setup();
  knob.setup();
  Wifi::Ap::setup(apOnStateChange);
  Wifi::Station::setup(stationOnStateChange);
  api.setup();
  HttpServer::setup(httpServerOnSettings);

  // read in the configuration
  config.deserialize();

  // Flag set up as complete
  setupComplete = true;
}

void loop() {
  resetButton.loop();
  button.loop();
  knob.loop();
  Wifi::Ap::loop();
  Wifi::Station::loop();
  HttpServer::loop();
}

void reset() {
  DEBUG_PRINT("Resetting: delay (ms): [%d]", RESET_DELAY);
  delay(RESET_DELAY);
  ESP.reset();
}

void flashStatus(unsigned int count) {
  statusLight.blink(count, BLINK_LENGTH);
}

void queryNetworkMode() {
  DEBUG_PRINT("TODO");
}

void toggleAccessPointMode() {
  DEBUG_PRINT("TODO");
}

void startWpsConfig() {
  DEBUG_PRINT("TODO");
}

void toggleWifi() {
  DEBUG_PRINT("TODO");
}

void restoreFactorySettings() {
  DEBUG_PRINT("TODO");
}

void lightOnUpdate(bool on, int brightness) {
  DEBUG_PRINT("new value: on: [%d]: brightness: [%d]", on, brightness);
}

void buttonOnRelease() {
  DEBUG_PRINT("toggle the light");
  light.toggle();
}

void knobInterruptDispatch() {
  knob.interrupt();
}

void knobOnChange(int direction) {
  DEBUG_PRINT("change the light brightness: change: [%d]", direction);
  light.changeBrightness(direction);
}

void apOnStateChange(Wifi::Ap::State state) {
  DEBUG_PRINT("new state: state: [%d]", static_cast<int>(state));
}

void stationOnStateChange(Wifi::Station::State state) {
  DEBUG_PRINT("new state: state: [%d]", static_cast<int>(state));
}

void saveConfig() {
  // only save if setup is complete
  if (setupComplete) {
    config.serialize();
  }
}

void httpServerOnSettings(const char *ssid, const char *password) {
  DEBUG_PRINT("new settings: ssid: [%s]: password: [%s]", ssid, password);
  stationConfig.setConfig(ssid, password);
}
