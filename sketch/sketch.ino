#include <Arduino.h>
#include <EEPROM.h>
#include <functional>

#include "src/Debug.hpp"

#include "src/FactorySettings.hpp"
#include "src/Button.hpp"
#include "src/RotaryEncoder.hpp"
#include "src/Blinker.hpp"
#include "src/Light.hpp"
#include "src/Storage.hpp"
#include "src/HttpServer.hpp"

#include "src/Wifi/Config.hpp"
#include "src/Wifi/Ap.hpp"
#include "src/Wifi/Station.hpp"

#include "src/Json/Allocator.hpp"
#include "src/Json/File.hpp"
#include "src/Json/Object.hpp"
#include "src/Json/Config.hpp"
#include "src/Json/HttpApi.hpp"

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

namespace ResetDelay {
  enum {
    RESET = 0,
    QUERY = 2000,
    ACCESS_POINT = 5000,
    WPS_CONFIG = 8000,
    WIFI = 11000,
    FACTORY_RESTORE = 14000
  };
};

#define POINTER_ARRAY_LENGTH(ARRAY) (sizeof(ARRAY)/sizeof(void*))

bool setupComplete = false;
void saveConfig();

void lightOnUpdate(bool on, int brightness);
Light light(D1, lightOnUpdate);

Blinker statusLight(D4, LOW);

void buttonOnRelease();
BUTTON_ON_RELEASE_PARAM(buttonParam, buttonOnRelease);
Button button(D7, BUTTON_DEBOUNCE_DELAY, buttonParam);

void flashStatus(unsigned int count);
void reset();
const Button::Delay resetDelay = {
  ResetDelay::RESET,
  NULL,
  reset
};
void queryNetworkMode();
const Button::Delay resetQueryDelay = {
  ResetDelay::QUERY,
  std::bind(&flashStatus, Blinks::QUERY),
  queryNetworkMode
};
void toggleAccessPointMode();
const Button::Delay resetAccessPointDelay = {
  ResetDelay::ACCESS_POINT,
  std::bind(&flashStatus, Blinks::ACCESS_POINT),
  toggleAccessPointMode
};
void startWpsConfig();
const Button::Delay resetWpsConfigDelay = {
  ResetDelay::WPS_CONFIG,
  std::bind(&flashStatus, Blinks::WPS_CONFIG),
  startWpsConfig
};
void toggleWifi();
const Button::Delay resetWifiDelay = {
  ResetDelay::WIFI,
  std::bind(&flashStatus, Blinks::WIFI),
  toggleWifi
};
void restoreFactorySettings();
const Button::Delay resetRestoreDelay = {
  ResetDelay::FACTORY_RESTORE,
  []() {
    flashStatus(Blinks::FACTORY_RESTORE);
    restoreFactorySettings();
  },
  NULL
};
const Button::Delay * resetButtonParam[] = {
  &resetDelay,
  &resetQueryDelay,
  &resetAccessPointDelay,
  &resetWpsConfigDelay,
  &resetWifiDelay,
  &resetRestoreDelay,
  NULL
};
Button resetButton(D2, BUTTON_DEBOUNCE_DELAY, resetButtonParam);

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
  &apConfig
};
Json::Config config(
  Json::Allocator<StaticJsonDocument<256>>::withDoc,
  POINTER_ARRAY_LENGTH(configSections),
  configSections,
  &configFile
);
Json::HttpApi api(
  HTTP_API_PREFIX,
  Json::Allocator<StaticJsonDocument<256>>::withDoc,
  POINTER_ARRAY_LENGTH(configSections),
  configSections,
  &HttpServer::server
);

void setup() {
  Serial.begin(115200);
  // TODO: We may not be concerned about
  // real random values but should probably
  // change this seed. However at present
  // this does still generate different values
  // every time
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
  static const Blinker::Pattern start = {0, BLINK_LENGTH};
  static const Blinker::Pattern other = {BLINK_LENGTH, BLINK_LENGTH};
  DEBUG_PRINT("count: [%u]", count);
  const Blinker::Pattern * pattern[count + 1];
  for (int i = 0; i < count; i++) {
    pattern[i] = i ? &other : &start;
  }
  pattern[count] = NULL;
  statusLight.blink(pattern);
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
