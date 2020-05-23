#include <Arduino.h>
#include <EEPROM.h>
#include <functional>

#include "src/Debug.hpp"

#include "src/FactorySettings.hpp"
#include "src/Button.hpp"
#include "src/RotaryEncoder.hpp"
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

#define POINTER_ARRAY_LENGTH(ARRAY) (sizeof(ARRAY)/sizeof(void*))

bool setupComplete = false;
void saveConfig();

void lightOnUpdate(bool on, int brightness);
Light light(D1, lightOnUpdate);

void buttonOnRelease();
Button button(D7, buttonOnRelease);

void resetButtonOnRelease();
Button resetButton(D2, resetButtonOnRelease);

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

void resetButtonOnRelease() {
  DEBUG_VAL(F("Resetting"), F("delay (ms)"), RESET_DELAY);
  delay(RESET_DELAY);
  ESP.reset();
}

void lightOnUpdate(bool on, int brightness) {
  DEBUG_LIST_START(F("new value"));
  DEBUG_LIST_VAL(F("on"), on);
  DEBUG_LIST_VAL(F("brightness"), brightness);
  DEBUG_LIST_END;
}

void buttonOnRelease() {
  DEBUG_MSG(F("toggle the light"));
  light.toggle();
}

void knobInterruptDispatch() {
  knob.interrupt();
}

void knobOnChange(int direction) {
  DEBUG_VAL(F("change the light brightness"), F("change"), direction);
  light.changeBrightness(direction);
}

void apOnStateChange(Wifi::Ap::State state) {
  DEBUG_VAL(F("new state"), F("state"), static_cast<int>(state));
}

void stationOnStateChange(Wifi::Station::State state) {
  DEBUG_VAL(F("new state"), F("state"), static_cast<int>(state));
}

void saveConfig() {
  // only save if setup is complete
  if (setupComplete) {
    config.serialize();
  }
}

void httpServerOnSettings(const char *ssid, const char *password) {
  DEBUG_LIST_START(F("new settings"));
  DEBUG_LIST_VAL(F("ssid"), ssid);
  DEBUG_LIST_VAL(F("password"), password);
  DEBUG_LIST_END;
  stationConfig.setConfig(ssid, password);
}
