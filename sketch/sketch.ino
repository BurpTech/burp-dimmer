#include <Arduino.h>
#include <functional>

#include "src/Debug.hpp"

#include "src/Button.hpp"
#include "src/RotaryEncoder.hpp"
#include "src/Light.hpp"
#include "src/Storage.hpp"
#include "src/Network.hpp"
#include "src/HttpServer.hpp"

#include "src/JsonFile.hpp"
#include "src/JsonConfig.hpp"

#define CONFIG_FILE_PATH "/config.json"
#define RESET_DELAY 1000

void lightOnUpdate(bool on, int brightness);
Light light(D1, lightOnUpdate);

void buttonOnRelease();
Button button(D7, buttonOnRelease);

void resetButtonOnRelease();
Button resetButton(D2, resetButtonOnRelease);

ICACHE_RAM_ATTR void knobInterruptDispatch();
void knobOnChange(int direction);
RotaryEncoder knob(D5, D6, knobInterruptDispatch, knobOnChange);

void networkOnStateChange(Network::State state);
void networkOnConfigChange();
void httpServerOnSettings(const char *ssid, const char *password);

using namespace std::placeholders; // for _1, _2
JsonFile configFile(CONFIG_FILE_PATH);
JsonConfigSection configSections[] = {
  JsonConfigSection(
    NETWORK_STATION_WIFI_CONFIG,
    std::bind(&WifiConfig::serialize, &Network::stationConfig, _1),
    std::bind(&WifiConfig::deserialize, &Network::stationConfig, _1)
  ),
  JsonConfigSection(
    NETWORK_STATION_AP_CONFIG,
    std::bind(&WifiConfig::serialize, &Network::apConfig, _1),
    std::bind(&WifiConfig::deserialize, &Network::apConfig, _1)
  )
};
JsonConfig<256> config(
  CONFIG_SECTION_ARRAY_LENGTH(configSections),
  configSections,
  std::bind(&JsonFile::write, &configFile, _1),
  std::bind(&JsonFile::read, &configFile, _1)
);

void setup() {
  Serial.begin(115200);
  Storage::begin();
  resetButton.setup();
  light.setup();
  button.setup();
  knob.setup();
  Network::setup(networkOnStateChange, networkOnConfigChange);
  HttpServer::setup(httpServerOnSettings);

  // read in the configuration
  config.deserialize();
}

void loop() {
  resetButton.loop();
  button.loop();
  knob.loop();
  Network::loop();
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

void networkOnStateChange(Network::State state) {
  DEBUG_VAL(F("new state"), F("state"), static_cast<int>(state));
}

void networkOnConfigChange() {
  config.serialize();
}

void httpServerOnSettings(const char *ssid, const char *password) {
  DEBUG_LIST_START(F("new settings"));
  DEBUG_LIST_VAL(F("ssid"), ssid);
  DEBUG_LIST_VAL(F("password"), password);
  DEBUG_LIST_END;
  Network::stationConfig.setConfig(ssid, password);
}
